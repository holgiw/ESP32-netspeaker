// Klangeffekte fuer den Audio-Task: Klangregler (Bass und Hoehen als Shelving-Filter), Hall (Freeverb) und Echo.
// Die Verarbeitung laeuft in Gleitkomma auf den Samples, die der Audio-Task an I2S gibt (32 Bit, links/rechts abwechselnd).
// Sound effects for the audio task: tone control (bass and treble as shelving filters), reverb (Freeverb) and echo.
// The processing runs in floating point on the samples the audio task hands to I2S (32 bit, left/right alternating).

#pragma once

#include <math.h>
#include <string.h>
#include <esp_heap_caps.h>
#include <esp_timer.h>

// Betriebsart des Effekts / mode of the effect
#define FX_OFF 0
#define FX_ROOM 1
#define FX_HALL 2
#define FX_CHURCH 3
#define FX_ECHO 4

// Speicher fuer die Verzoegerungsleitungen (Gleitkommawerte, im PSRAM): Hall braucht rund 28000, Echo 2 x 0,35 s bei 48 kHz.
// Memory for the delay lines (floats, in PSRAM): reverb needs about 28000, echo 2 x 0.35 s at 48 kHz.

#define FX_POOL_FLOATS 34000

struct FxBiquad {
    float b0 = 1, b1 = 0, b2 = 0, a1 = 0, a2 = 0;
    float z1[2] = {0, 0};
    float z2[2] = {0, 0};
    inline float run(int ch, float x) {
        float y = b0 * x + z1[ch];
        z1[ch] = b1 * x - a1 * y + z2[ch];
        z2[ch] = b2 * x - a2 * y;
        return y;
    }
};

class FxEngine {
  public:
    // Einstellungen: vom Web-Task gesetzt, vom Audio-Task uebernommen (kleine Werte, einzelne Schreibzugriffe).
    // Settings: set by the web task, taken over by the audio task (small values, single writes).
    volatile int mode = FX_OFF;
    volatile int wet = 30;       // 0..100 %
    volatile int bass = 0;       // -12..12 dB
    volatile int treble = 0;     // -12..12 dB
    volatile int pan = 0;        // Wandern: 0 aus, 1 links->rechts, 2 rechts->links, 3 hin und her, 4 fest links, 5 fest rechts / sweep: 0 off, 1 left->right, 2 right->left, 3 back and forth, 4 fixed left, 5 fixed right
    volatile int panDs = 30;     // Dauer eines Durchgangs in 0,1 s (5..200) / duration of one pass in 0.1 s (5..200)
    volatile uint32_t cpuUs = 0; // Rechenzeit seit dem letzten Zuruecksetzen / processing time since the last reset
    volatile uint32_t cpuFrames = 0;

    // Verzoegerungsleitungen beim naechsten Aufruf leeren (neue Ansage).
    // Clear the delay lines at the next call (new announcement).
    void flush() {
        needClear = true;
    }

    bool active() const {
        return mode != FX_OFF || bass != 0 || treble != 0 || pan != 0;
    }

    // Auslastung des Audio-Kerns durch die Effekte in Prozent (Mittel seit dem Zuruecksetzen).
    // Load of the audio core caused by the effects in percent (average since the reset).
    float loadPercent() const {
        if (cpuFrames == 0 || rate == 0) return 0;
        return 100.0f * ((float)cpuUs / 1e6f) / ((float)cpuFrames / (float)rate);
    }
    void resetLoad() {
        cpuUs = 0;
        cpuFrames = 0;
    }

    void process(int32_t* buf, int words, uint32_t sampleRate) {
        if (!active() || sampleRate < 8000 || sampleRate > 48000 || words < 2) return;
        int64_t t0 = esp_timer_get_time();
        int m = mode, w = wet, b = bass, t = treble;
        int pn = pan, ps = panDs;
        if (pn != curPan || ps != curPanDs) {
            curPan = pn;
            curPanDs = ps;
            panReset();
        }
        float panInc = 1.0f / ((float)(ps < 5 ? 5 : ps) * 0.1f * (float)sampleRate);

        // Nach einer Pause (kein Ton) die Verzoegerungsleitungen leeren, sonst klingt ein alter Hall an.
        // After a pause (no sound) clear the delay lines, otherwise an old reverb tail sounds again.

        if (needClear || t0 - lastCall > 400000) {
            clearState();
            needClear = false;
        }
        lastCall = t0;
        if (sampleRate != rate || m != curMode || b != curBass || t != curTreble) configure(sampleRate, m, b, t);
        if (!ok) return;
        float wetF = (float)w / 100.0f;
        float dry = 1.0f - 0.35f * wetF;
        const float k = 1.0f / 2147483648.0f;
        int frames = words / 2;
        for (int i = 0; i < frames; i++) {
            float l = (float)buf[2 * i] * k;
            float r = (float)buf[2 * i + 1] * k;
            if (eqOn) {
                l = tone(0, l);
                r = tone(1, r);
            }
            float ol = l, orr = r;
            if (curMode == FX_ECHO) {
                float el = echoL[ei], er = echoR[ei];
                echoL[ei] = l + 0.38f * el;
                echoR[ei] = r + 0.38f * er;
                if (++ei >= echoLen) ei = 0;
                ol = l * dry + el * wetF * 0.9f;
                orr = r * dry + er * wetF * 0.9f;
            } else if (curMode != FX_OFF) {
                float in = (l + r) * 0.015f;
                float sl = 0, sr = 0;
                for (int c = 0; c < 8; c++) {
                    sl += comb(cl[c], in);
                    sr += comb(cr[c], in);
                }
                for (int a = 0; a < 4; a++) {
                    sl = allpass(al[a], sl);
                    sr = allpass(ar[a], sr);
                }
                float g = wetF * 3.0f;
                ol = l * dry + sl * g;
                orr = r * dry + sr * g;
            }
            if (curPan != 0) {

                // Wandern: die Mitte beider Kanaele wird mit gleichbleibender Leistung zwischen links und rechts verschoben (Mitte = Originalpegel).
                // Sweep: the mid of both channels is moved between left and right with constant power (center = original level).

                float mid = 0.5f * (ol + orr);
                float th = panPos * 1.5707963f;
                ol = mid * cosf(th) * 1.41421356f;
                orr = mid * sinf(th) * 1.41421356f;
                panPos += panDir * panInc;
                if (curPan == 3) {
                    if (panPos >= 1.0f) {
                        panPos = 1.0f;
                        panDir = -1.0f;
                    } else if (panPos <= 0.0f) {
                        panPos = 0.0f;
                        panDir = 1.0f;
                    }
                } else {
                    if (panPos > 1.0f) panPos = 1.0f;
                    if (panPos < 0.0f) panPos = 0.0f;
                }
            }
            buf[2 * i] = clip32(ol);
            buf[2 * i + 1] = clip32(orr);
        }
        cpuUs = cpuUs + (uint32_t)(esp_timer_get_time() - t0);
        cpuFrames = cpuFrames + frames;
    }

  private:
    struct Comb {
        float* b = nullptr;
        int len = 0, idx = 0;
        float store = 0;
    };
    struct Allpass {
        float* b = nullptr;
        int len = 0, idx = 0;
    };

    float* pool = nullptr;
    bool ok = false;
    uint32_t rate = 0;
    int curMode = -1, curBass = 999, curTreble = 999;
    int curPan = 0, curPanDs = 30;
    float panPos = 0.0f, panDir = 1.0f;

    // Startposition der Bewegung: bei rechts->links beginnt sie rechts, sonst links.
    // Start position of the sweep: right->left starts at the right, otherwise at the left.
    void panReset() {
        if (curPan == 4 || curPan == 5) {   // feste Position: 4 links, 5 rechts / fixed position: 4 left, 5 right
            panPos = curPan == 5 ? 1.0f : 0.0f;
            panDir = 0.0f;
        } else if (curPan == 2) {
            panPos = 1.0f;
            panDir = -1.0f;
        } else {
            panPos = 0.0f;
            panDir = 1.0f;
        }
    }
    bool eqOn = false;
    volatile bool needClear = false;
    int64_t lastCall = 0;
    float fb = 0.8f, damp1 = 0.4f, damp2 = 0.6f;
    Comb cl[8], cr[8];
    Allpass al[4], ar[4];
    float* echoL = nullptr;
    float* echoR = nullptr;
    int echoLen = 0, ei = 0;
    FxBiquad lo, hi;

    static inline int32_t clip32(float x) {
        if (x > 0.999f) x = 0.999f;
        if (x < -0.999f) x = -0.999f;
        return (int32_t)(x * 2147483648.0f);
    }

    inline float tone(int ch, float x) {
        return hi.run(ch, lo.run(ch, x));
    }

    inline float comb(Comb& c, float in) {
        float out = c.b[c.idx];
        c.store = out * damp2 + c.store * damp1;
        c.b[c.idx] = in + c.store * fb;
        if (++c.idx >= c.len) c.idx = 0;
        return out;
    }

    inline float allpass(Allpass& a, float in) {
        float bo = a.b[a.idx];
        float out = -in + bo;
        a.b[a.idx] = in + bo * 0.5f;
        if (++a.idx >= a.len) a.idx = 0;
        return out;
    }

    void clearState() {
        panReset();
        if (pool) memset(pool, 0, sizeof(float) * FX_POOL_FLOATS);
        for (int i = 0; i < 8; i++) {
            cl[i].store = 0;
            cr[i].store = 0;
            cl[i].idx = 0;
            cr[i].idx = 0;
        }
        ei = 0;
        for (int i = 0; i < 4; i++) {
            al[i].idx = 0;
            ar[i].idx = 0;
        }
        lo.z1[0] = lo.z1[1] = lo.z2[0] = lo.z2[1] = 0;
        hi.z1[0] = hi.z1[1] = hi.z2[0] = hi.z2[1] = 0;
    }

    // RBJ-Shelving-Filter; low = Bass (Tiefen anheben/absenken), sonst Hoehen.
    // RBJ shelving filter; low = bass, otherwise treble.

    static void shelf(FxBiquad& q, bool low, float f, float dB, float fs) {
        float A = powf(10.0f, dB / 40.0f);
        float w0 = 2.0f * (float)M_PI * f / fs;
        float cw = cosf(w0), sw = sinf(w0);
        float alpha = sw / 2.0f * 1.41421356f;
        float sA = sqrtf(A);
        float b0, b1, b2, a0, a1, a2;
        if (low) {
            b0 = A * ((A + 1) - (A - 1) * cw + 2 * sA * alpha);
            b1 = 2 * A * ((A - 1) - (A + 1) * cw);
            b2 = A * ((A + 1) - (A - 1) * cw - 2 * sA * alpha);
            a0 = (A + 1) + (A - 1) * cw + 2 * sA * alpha;
            a1 = -2 * ((A - 1) + (A + 1) * cw);
            a2 = (A + 1) + (A - 1) * cw - 2 * sA * alpha;
        } else {
            b0 = A * ((A + 1) + (A - 1) * cw + 2 * sA * alpha);
            b1 = -2 * A * ((A - 1) + (A + 1) * cw);
            b2 = A * ((A + 1) + (A - 1) * cw - 2 * sA * alpha);
            a0 = (A + 1) - (A - 1) * cw + 2 * sA * alpha;
            a1 = 2 * ((A - 1) - (A + 1) * cw);
            a2 = (A + 1) - (A - 1) * cw - 2 * sA * alpha;
        }
        q.b0 = b0 / a0;
        q.b1 = b1 / a0;
        q.b2 = b2 / a0;
        q.a1 = a1 / a0;
        q.a2 = a2 / a0;
    }

    // Stellt Filter und Verzoegerungsleitungen auf Abtastrate, Betriebsart und Reglerwerte ein.
    // Sets up filters and delay lines for the sample rate, mode and control values.

    void configure(uint32_t fs, int m, int b, int t) {
        rate = fs;
        curMode = m;
        curBass = b;
        curTreble = t;
        eqOn = b != 0 || t != 0;
        ok = true;
        if (eqOn) {
            shelf(lo, true, 200.0f, (float)b, (float)fs);
            shelf(hi, false, 4000.0f, (float)t, (float)fs);
        }
        if (m == FX_OFF) return;
        if (!pool) {
            pool = (float*)heap_caps_calloc(FX_POOL_FLOATS, sizeof(float), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
            if (!pool) {
                ok = false;
                return;
            }
        }
        memset(pool, 0, sizeof(float) * FX_POOL_FLOATS);
        float* p = pool;
        if (m == FX_ECHO) {
            echoLen = (int)(0.35f * fs);
            if (echoLen * 2 > FX_POOL_FLOATS) echoLen = FX_POOL_FLOATS / 2;
            echoL = p;
            echoR = p + echoLen;
            ei = 0;
            return;
        }

        // Freeverb: Laengen bei 44,1 kHz, auf die Abtastrate umgerechnet; rechts um 23 Samples versetzt.
        // Freeverb: lengths at 44.1 kHz, scaled to the sample rate; the right side is offset by 23 samples.

        static const int combT[8] = {1116, 1188, 1277, 1356, 1422, 1491, 1557, 1617};
        static const int allT[4] = {556, 441, 341, 225};
        int need = 0;
        for (int i = 0; i < 8; i++) need += (int)((combT[i] * (float)fs / 44100.0f) + 0.5f) * 2 + 2 * 24;
        for (int i = 0; i < 4; i++) need += (int)((allT[i] * (float)fs / 44100.0f) + 0.5f) * 2 + 2 * 24;
        if (need > FX_POOL_FLOATS) {
            ok = false;
            return;
        }
        for (int i = 0; i < 8; i++) {
            int lL = (int)((combT[i] * (float)fs / 44100.0f) + 0.5f), lR = (int)(((combT[i] + 23) * (float)fs / 44100.0f) + 0.5f);
            cl[i] = Comb{p, lL, 0, 0};
            p += lL;
            cr[i] = Comb{p, lR, 0, 0};
            p += lR;
        }
        for (int i = 0; i < 4; i++) {
            int lL = (int)((allT[i] * (float)fs / 44100.0f) + 0.5f), lR = (int)(((allT[i] + 23) * (float)fs / 44100.0f) + 0.5f);
            al[i] = Allpass{p, lL, 0};
            p += lL;
            ar[i] = Allpass{p, lR, 0};
            p += lR;
        }

        // Raumgroesse (Rueckkopplung) und Daempfung je Voreinstellung.
        // Room size (feedback) and damping per preset.

        float room = m == FX_ROOM ? 0.55f : (m == FX_HALL ? 0.80f : 0.93f);
        float damp = m == FX_ROOM ? 0.55f : (m == FX_HALL ? 0.40f : 0.25f);
        fb = room * 0.28f + 0.7f;
        damp1 = damp * 0.4f;
        damp2 = 1.0f - damp1;
    }
};
