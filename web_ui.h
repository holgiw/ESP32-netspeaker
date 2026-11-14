#pragma once

// Web-Oberflaeche: eine Hub-Seite mit Tabs, Statusleiste, JSON-API, Datei-Upload, Export/Import.
// Web interface: one hub page with tabs, status bar, JSON API, file upload, export/import.

// ---------------------------------------------------------------------------
// Stil, Seitenkopf / style, page head

static const char PAGE_CSS[] PROGMEM = R"css(
:root{--bg:#10151a;--panel:#1a2129;--panel-border:#2a333c;--text:#e8edf2;--muted:#8f9ba7;--accent:#f5a623;--accent-dim:#7a530f;--ok:#3ddc84;--bad:#ff5c5c;--sans:system-ui,-apple-system,"Segoe UI",Roboto,sans-serif;--mono:ui-monospace,"SFMono-Regular",Menlo,Consolas,monospace;}
body{font-family:Arial,Helvetica,sans-serif;text-align:center;margin:0;background:var(--bg);color:var(--text);}
.page{padding:0 8px 40px;}
input,select,button,textarea{margin:10px;padding:10px;width:80%;box-sizing:border-box;background:#0d1216;color:var(--text);border:1px solid var(--panel-border);border-radius:6px;font-family:inherit;}
input[type=checkbox],input[type=radio]{width:auto;}
button,button[type=submit],input[type=submit]{background:var(--accent);color:#1a1200;font-weight:bold;border:none;cursor:pointer;}
button:hover,input[type=submit]:hover{background:#ffb84d;}
h1,h2,h3{color:var(--text);}
hr{border:0;height:1px;background-color:var(--panel-border);margin:20px 0;}
table{margin:auto;border-collapse:collapse;}
th,td{padding:8px 10px;text-align:left;border:1px solid var(--panel-border);}
a{color:var(--accent);}
small{color:var(--muted);}
.topbar{display:flex;flex-wrap:wrap;align-items:center;gap:.6rem 1.2rem;padding:.9rem 1rem;border-bottom:1px solid var(--panel-border);position:sticky;top:0;background:var(--bg);z-index:5;}
.brand{display:flex;align-items:baseline;gap:.5rem;margin-right:auto;}
.brand-mark{font-family:var(--mono);color:var(--accent);font-size:.8rem;letter-spacing:.05em;}
.topbar h1{font-size:1.15rem;margin:0;letter-spacing:.02em;}
h1 a.host-link{color:inherit;text-decoration:none;border-bottom:1px dashed var(--muted);}
h1 a.host-link:hover{color:var(--accent);border-bottom-color:var(--accent);}
.ip-hint{font-family:var(--mono);font-size:.7rem;color:var(--muted);}
.ip-hint a{color:inherit;font-size:inherit;text-decoration:none;border-bottom:1px dashed var(--muted);}
.ip-hint a:hover{color:var(--accent);border-bottom-color:var(--accent);}
.status-strip{display:flex;gap:.9rem;flex-wrap:wrap;}
.status{display:flex;align-items:center;gap:.4rem;font-size:.8rem;color:var(--muted);}
.status[hidden]{display:none;}
.statval{font-family:var(--mono);color:var(--text);}
.dot{width:.55rem;height:.55rem;border-radius:50%;background:var(--bad);box-shadow:0 0 0 3px rgba(255,92,92,.15);}
.dot.ok{background:var(--ok);box-shadow:0 0 0 3px rgba(61,220,132,.18);}
.dot.na,.dot.idle{background:var(--muted);box-shadow:0 0 0 3px rgba(143,155,167,.18);}
.dot.syncing{background:var(--accent);box-shadow:0 0 0 3px rgba(245,166,35,.18);animation:dotBlink 1s ease-in-out infinite;}
.dot.playing{background:var(--ok);box-shadow:0 0 0 3px rgba(61,220,132,.18);animation:dotBlink 1s ease-in-out infinite;}
@keyframes dotBlink{0%,100%{opacity:1;}50%{opacity:.25;}}
@media (prefers-reduced-motion:reduce){.dot.syncing,.dot.playing{animation:none;opacity:.6;}}
.datetime{font-family:var(--mono);font-size:.8rem;color:var(--muted);}
.offline-hint{display:none;color:var(--bad);font-size:.75rem;margin-left:.3rem;}
.offline-hint.show{display:inline;}
.refresh-btn{display:inline-flex;align-items:center;justify-content:center;box-sizing:border-box;background:transparent;border:1px solid var(--panel-border);color:var(--text);border-radius:.4rem;width:2rem;height:2rem;padding:0;margin:0;font-size:1rem;line-height:1;cursor:pointer;text-decoration:none;}
.refresh-btn:hover{background:transparent;border-color:var(--accent);color:var(--accent);}
.refresh-btn:focus-visible{outline:2px solid var(--accent);outline-offset:1px;}
.reset-btn{background:transparent;border:1px solid var(--panel-border);color:var(--bad);border-radius:.4rem;width:2rem;height:2rem;padding:0;margin:0;font-size:1rem;line-height:1;cursor:pointer;}
.reset-btn:hover{background:rgba(255,92,92,.12);border-color:var(--bad);}
.reset-btn:focus-visible{outline:2px solid var(--bad);outline-offset:1px;}
.tabctrl{display:none;}
.tabnav{margin:20px auto;max-width:900px;display:flex;flex-wrap:wrap;justify-content:center;gap:4px;}
.tabnav label{background:var(--panel);border:1px solid var(--panel-border);color:var(--muted);padding:8px 16px;border-radius:8px 8px 0 0;cursor:pointer;font-weight:bold;}
.tabpanel{display:none;}
.card{background:var(--panel);border:1px solid var(--panel-border);border-radius:10px;max-width:500px;margin:15px auto;padding:12px 16px;text-align:left;}
.card h3{margin:.2rem 0 .6rem;text-align:center;}
.card.wide{max-width:700px;}
.sub{border:1px solid var(--panel-border);border-radius:8px;padding:4px 12px 10px;margin:10px 0;}
.sub h4{margin:.5rem 0 .6rem;font-size:.95rem;color:var(--accent);text-align:left;}
.pinrow{justify-content:flex-start;}
.pinlabel{display:inline-block;width:11rem;text-align:right;color:var(--muted);}
select.pinsel.dup{outline:2px solid var(--bad);}
.pinwarn{display:block;color:var(--bad);min-height:1.2em;}
.row{display:flex;gap:6px;align-items:center;flex-wrap:wrap;justify-content:center;}
.row input,.row select,.row button{margin:6px;}
.flash{background:#d4edda;color:#155724;border:1px solid #c3e6cb;border-radius:6px;padding:8px 12px;margin:10px auto;max-width:500px;}
.codewrap{position:relative;}
.copy-btn{position:absolute;top:6px;right:6px;width:auto;margin:0;padding:3px 10px;font-size:.75rem;font-weight:normal;background:var(--panel);border:1px solid var(--panel-border);color:var(--text);border-radius:.4rem;cursor:pointer;}
.copy-btn:hover{background:var(--panel);border-color:var(--accent);color:var(--accent);}
.doc p,.doc li{font-size:.9rem;line-height:1.45;}
.doc table{width:100%;font-size:.85rem;}
.doc td,.doc th{text-align:left;}
.mqtt{font-size:1.05rem;}
.mqtt h3{font-size:1.3rem;}
.mqtt input{font-size:1.05rem;}
.mqtt label{display:block;margin:.6rem 0 .1rem;font-weight:bold;}
.mqtt table{width:100%;margin:12px 0;}
.mqtt th{background:var(--bg);font-size:.95rem;}
.mqtt td{vertical-align:top;padding:9px 10px;font-size:1rem;}
.mqtt code{font-family:var(--mono);font-size:.95rem;color:var(--accent);overflow-wrap:anywhere;word-break:normal;}
.mqtt td:first-child{min-width:310px;}
.mqtt .ex{display:block;margin:2px 0 6px;color:var(--text);}
.mqtt .kind{display:inline-block;padding:1px 8px;border-radius:10px;font-size:.8rem;border:1px solid var(--panel-border);color:var(--muted);}
.mqtt .kind.cmd{color:var(--accent);border-color:var(--accent-dim);}
.mqtt .kind.msg{color:var(--ok);border-color:var(--ok);}
.flash.warn{background:#fff3cd;color:#856404;border-color:#ffeeba;}
.flash.bad{background:#f8d7da;color:#721c24;border-color:#f5c6cb;font-weight:600;}
.res-ok{background:#d4edda;color:#155724;border:1px solid #c3e6cb;border-radius:6px;padding:8px 12px;margin:10px auto;max-width:400px;}
.res-bad{background:#f8d7da;color:#721c24;border:1px solid #f5c6cb;border-radius:6px;padding:8px 12px;margin:10px auto;max-width:400px;}
textarea{height:110px;resize:vertical;}
pre.code{text-align:left;white-space:pre-wrap;word-break:break-all;font-family:var(--mono);font-size:.75rem;color:var(--muted);}
)css";

#include "wiring_svg.h"
#include "wiring_view_svg.h"

static const char TAB_KEYS[][12] = {"mp3", "ansage", "sd", "radio", "pins", "audio", "mqtt", "wlan", "zeit", "sicherung", "status", "log", "doku"};
static const char* const TAB_LABELS[] = {"MP3 (Flash)", "Ansage", "SD-Karte", "Webradio", "Eing&auml;nge", "Audio", "MQTT", "WLAN", "Zeit", "Sicherung", "Status", "Log", "Doku"};
static const char* const TAB_TIPS[] = {"MP3-Dateien im Ger&auml;t hochladen und abspielen", "Text ansagen, stoppen, Lautst&auml;rke", "Dateien der SD-Karte abspielen, hochladen und verwalten", "Webradio-URL abspielen und bis zu 30 Sender speichern", "Freie Pins mit Pull-up: bei Kontakt nach GND eine Ansage oder MP3-Datei abspielen", "Anschl&uuml;sse (Pins von Verst&auml;rker und SD-Karte), Lautst&auml;rke, &Uuml;berblenden, Start und Sprachausgabe (VoiceRSS)", "MQTT-Broker und Basis-Topic", "Hostname und WLAN-Zugangsdaten", "Zeitserver und Zeitzone", "Einstellungen sichern und wieder einlesen, wahlweise mit WLAN-Zugangsdaten und Dateien im Flash", "Zustand des Ger&auml;ts", "Ereignisprotokoll", "Alle REST- und MQTT-Aufrufe zum Kopieren"};
static const int TAB_COUNT = 13;

// ⓘ-Hinweis mit Erklaerung als Tooltip (title) - der Punkt am Satzende kommt hier dazu; im Text keine einfachen Anfuehrungszeichen.
// ⓘ note with an explanation as tooltip (title) - the full stop at the end is added here; no single quotes in the text.

String infoTip(const String& text) {
    return "<span title='" + text + ".' style='cursor:help;'>&#9432;</span>";
}

String htmlEsc(const String& s) {
    String out;
    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c == '&') out += "&amp;";
        else if (c == '<') out += "&lt;";
        else if (c == '>') out += "&gt;";
        else if (c == '\'') out += "&#39;";
        else if (c == '"') out += "&quot;";
        else out += c;
    }
    return out;
}

// Text fuer Tooltip und aria-label eines Punktes; ohne Umlaute, weil JavaScript keine HTML-Entities aufloest.
// Text for the tooltip and aria-label of a dot; without umlauts because JavaScript does not decode HTML entities.

String dotStatusText(const String& label, const String& state) {
    String t = "Nicht verfuegbar";
    if (state == "ok") t = "OK";
    else if (state == "syncing") t = "Aktiv";
    else if (state == "playing") t = "Spielt";
    else if (state == "idle") t = "Leerlauf";
    else if (state == "bad") t = "Fehler";
    return label + ": " + t;
}

String statusDotHtml(const String& key, const String& label, const String& state, bool gated, bool present) {
    String title = htmlEsc(dotStatusText(label, state));
    String cls = state == "na" ? " na" : (state == "ok" ? " ok" : (state == "syncing" ? " syncing" : (state == "playing" ? " playing" : (state == "idle" ? " idle" : ""))));
    String h = "<span class='status' id='status-" + key + "'" + ((gated && !present) ? " hidden" : "") + ">";
    h += "<i id='dot-" + key + "' class='dot" + cls + "' role='img' title='" + title + "' aria-label='" + title + "'></i>" + label + "</span>";
    return h;
}

String formatNow() {
    if (!timeIsValid()) return "";
    char buf[24];
    time_t now = time(nullptr);
    struct tm timeinfo;
    localtime_r(&now, &timeinfo);
    strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M", &timeinfo);
    return String(buf);
}

bool mqttGatedPresent() {
    return mqttEverConnected;
}

bool voiceGatedPresent() {
    return voiceEver;
}

// Die Punkte hier und in handleTopbarStatus() muessen dieselben Bedingungen nutzen, sonst stimmen Erstansicht und Abfrage nicht ueberein.
// The dots here and in handleTopbarStatus() must use the same conditions, otherwise first paint and poll disagree.

String topbarHtml() {
    String ip = apActive && WiFi.status() != WL_CONNECTED ? WiFi.softAPIP().toString() : WiFi.localIP().toString();
    String h = "<header class='topbar'><div class='brand'><span class='brand-mark'>" PROJECT_TAG "</span>";
    h += "<h1><a class='host-link' href='http://" + cfg.host + ".local/'>" + htmlEsc(cfg.host) + "</a></h1>";
    h += "<span class='ip-hint'><a href='http://" + ip + "/'>" + ip + "</a></span></div>";
    h += "<div class='status-strip'>";
    h += "<span class='status' title='Aktuelle Lautst&auml;rke (0 bis 100)'>Lautst&auml;rke: <span id='value-vol' class='statval'>" + String(cfg.vol) + "/" + String(VOLUME_MAX) + "</span></span>";
    if (cfg.mqttServer.length() > 0) h += statusDotHtml("mqtt", "MQTT", mqttDotState(), true, mqttGatedPresent());
    if (cfg.vkey.length() > 0) h += statusDotHtml("voice", "VoiceRSS", voiceDotState(), true, voiceGatedPresent());
    h += statusDotHtml("audio", "Audio", audioDotState(), false, true);
    h += statusDotHtml("time", "Zeit", timeDotState(), false, true);
    h += "</div><div id='topbar-datetime' class='datetime'>" + formatNow() + "</div>";
    h += "<span id='topbar-offline-hint' class='offline-hint'>&#9888; Verbindung verloren</span>";
    h += "<a class='refresh-btn' id='langBtn' href='#' style='display:none' title='Sprache / Language'></a>";
    h += "<button type='button' class='reset-btn' onclick=\"if(confirm('ESP32 jetzt neu starten?')){fetch('/restart',{method:'POST'});setTimeout(function(){location.reload();},5000);}\" title='Neu starten'>&#9211;</button>";
    h += "</header>";
    return h;
}

static const char TOPBAR_JS[] PROGMEM = R"js(
(function(){
  function setStatusDot(id,state,title){var el=document.getElementById(id);if(!el)return;
    el.classList.toggle('ok',state==='ok');el.classList.toggle('syncing',state==='syncing');el.classList.toggle('playing',state==='playing');el.classList.toggle('idle',state==='idle');el.classList.toggle('na',state==='na');
    if(title){el.title=title;el.setAttribute('aria-label',title);}}
  function setPresent(id,p){var el=document.getElementById(id);if(el)el.hidden=!p;}
  function setValue(id,t){var el=document.getElementById(id);if(el)el.textContent=t;}
  function setOnline(ok){var h=document.getElementById('topbar-offline-hint');if(h)h.classList.toggle('show',!ok);}
  var fails=0;
  function poll(){
    fetch('/api/topbarStatus',{cache:'no-store'}).then(function(r){return r.json();}).then(function(s){
      fails=0;setOnline(true);
      setStatusDot('dot-mqtt',s.mqtt,s.mqttTitle);setPresent('status-mqtt',s.mqttPresent);
      setStatusDot('dot-voice',s.voice,s.voiceTitle);setPresent('status-voice',s.voicePresent);
      setStatusDot('dot-audio',s.audio,s.audioTitle);
      setStatusDot('dot-time',s.time,s.timeTitle);
      setValue('value-vol',s.volValue);
      var dt=document.getElementById('topbar-datetime');if(dt)dt.textContent=s.datetime;
    }).catch(function(){fails++;if(fails>=2)setOnline(false);});
  }
  var timer=null;
  function start(){if(timer)return;poll();timer=setInterval(poll,5000);}
  function stop(){if(!timer)return;clearInterval(timer);timer=null;}
  document.addEventListener('visibilitychange',function(){if(document.hidden)stop();else start();});
  if(!document.hidden)start();
})();
function loadStations(inp){
  var f=inp.files[0];if(!f)return;
  if(!confirm('Die gespeicherte Senderliste wird durch die Datei ersetzt. Fortfahren?')){inp.value='';return;}
  var rd=new FileReader();
  rd.onload=function(){fetch('/importstations',{method:'POST',headers:{'Content-Type':'text/plain'},body:rd.result}).then(function(r){return r.text();}).then(function(t){
    alert(t.indexOf('OK|')===0?t.substring(3):('Fehler: '+t.substring(5)));location.href='/?tab=radio';});};
  rd.readAsText(f);
}
)js";

// ---------------------------------------------------------------------------
// Tabs / tabs

String selectOptions(const char* const* values, const char* const* labels, int count, const String& current) {
    String h;
    for (int i = 0; i < count; i++) {
        h += "<option value='" + String(values[i]) + "'" + (current == values[i] ? " selected" : "") + ">" + labels[i] + "</option>";
    }
    return h;
}

static const char* const LANG_VALUES[] = {"de-de", "en-gb", "en-us", "fr-fr", "es-es", "it-it", "nl-nl", "pt-pt", "pl-pl", "sv-se", "da-dk"};
static const char* const LANG_LABELS[] = {"Deutsch (de-de)", "English UK (en-gb)", "English US (en-us)", "Fran&ccedil;ais (fr-fr)", "Espa&ntilde;ol (es-es)", "Italiano (it-it)", "Nederlands (nl-nl)", "Portugu&ecirc;s (pt-pt)", "Polski (pl-pl)", "Svenska (sv-se)", "Dansk (da-dk)"};
static const int LANG_COUNT = 11;

static const char* const FMT_VALUES[] = {"8khz_16bit_mono", "22khz_16bit_mono", "44khz_16bit_mono", "44khz_16bit_stereo"};
static const char* const FMT_LABELS[] = {"8 kHz mono (klein)", "22 kHz mono (Standard)", "44 kHz mono", "44 kHz stereo"};

// Die Auswahl der Stimmen wird im Browser je nach gewaehlter Sprache gefuellt (VOICES in PAGE_JS); "Andere ..." erlaubt eigene Namen.
// The voice choices are filled in the browser depending on the selected language (VOICES in PAGE_JS); "Andere ..." allows own names.

String nowPlayingRow();

// Lautstaerkeregler ganz oben in den Tabs MP3, Ansage, SD-Karte und Webradio; alle Regler zeigen denselben Wert.
// Volume slider at the very top of the tabs MP3, Ansage, SD-Karte and Webradio; all sliders show the same value.

String volumeRow() {
    return "<div class='row volrow'><label>Lautst&auml;rke <input type='range' class='volrange' min='0' max='" + String(VOLUME_MAX) + "' value='" + String(cfg.vol) + "' style='width:200px' oninput='volShow(this.value)' onchange='setVol(this.value)'> <span class='volshow' style='display:inline-block;min-width:76px'>" + String(cfg.vol) + " / " + String(VOLUME_MAX) + "</span></label><button type='button' class='stopbtn' onclick='stopNow()' style='width:auto;padding:6px 16px;margin:0 4px 0 12px' disabled>&#9632; Stopp</button><button type='button' class='mutebtn' onclick='muteToggle()' style='width:auto;padding:6px 16px;margin:0 8px 0 4px'>Stumm</button> " + infoTip("Lautst&auml;rke 0 bis 100; wird sofort &uuml;bernommen und gespeichert. Stopp: beendet die Wiedergabe sofort, auch ein Webradio, ohne Fortsetzung. Stumm: blendet den Ton sanft aus und wieder ein, die eingestellte Lautst&auml;rke bleibt unver&auml;ndert. Stumm gilt f&uuml;r Webradio, Text-Ansagen (Uhrzeit, Mail ...) und MP3 von der SD-Karte; MP3 aus dem Flash bleiben h&ouml;rbar") + "</div>";
}

String panelSpeak() {
    String h = volumeRow() + nowPlayingRow();
    h += "<div class='card'><h3>Text ansagen</h3>";
    h += "<div class='row'>Text zum Ansagen " + infoTip("Text, der &uuml;ber VoiceRSS angesagt wird (h&ouml;chstens 500 Zeichen)") + "</div>";
    h += "<textarea id='sayText' maxlength='" + String(TTS_MAX_CHARS) + "' placeholder='Text zum Ansagen'></textarea>";
    h += "<div class='row'><select id='sayLang' onchange=\"fillVoiceSel('sayVoice',this.value,false)\" style='width:210px'><option value=''>Standard (" + htmlEsc(cfg.vlang) + ")</option>" + selectOptions(LANG_VALUES, LANG_LABELS, LANG_COUNT, "") + "</select> " + infoTip("Sprache der Ansage; Standard ist die Sprache aus dem Tab Audio") + "";
    h += "<select id='sayVoice' onchange='voiceChosen(this)' style='width:210px'><option value=''>Standard (VoiceRSS)</option></select> " + infoTip("Stimme f&uuml;r diese Ansage; Standard = gespeicherte Stimme bzw. Standardstimme der Sprache") + "</div>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' id='saySave' style='width:auto;margin:0;'>Text speichern</label> " + infoTip("Speichert die Sprachdatei dieses Textes beim n&auml;chsten Sprechen dauerhaft, bevorzugt auf der SD-Karte (Ordner /ansagen), sonst im Ger&auml;t (Tab MP3 (Flash)). Danach wird der Haken wieder entfernt. Gespeicherte Texte werden bei gleicher Sprache, Stimme und gleichem Tempo gespielt, ohne VoiceRSS zu fragen, auch ohne Internet. Die aktuellen Klangeffekte werden mit gespeichert (im Dateinamen, zum Beispiel _halle40_b3_t-2) und gelten nur f&uuml;r diesen Text, unabh&auml;ngig von den sp&auml;teren Einstellungen") + "</div>";
    h += "<div class='row'><button type='button' onclick='sayNow()' style='width:150px'>Sprechen</button> " + infoTip("Sprechen: sagt den Text jetzt an, ein laufendes Webradio l&auml;uft danach weiter") + "</div>";
    h += "<div id='sayResult'></div><div class='row'><small id='playState'></small></div></div>";
    h += "<div class='card'><h3>Klangeffekte " + infoTip("Hall und Echo wirken auf Ansagen, Klangregler und Wandern auch auf abgespielte Dateien, nie auf Webradio. &Auml;nderungen gelten sofort und bleiben gespeichert. Der Verst&auml;rker spielt in Mono, der Raumeindruck ist deshalb begrenzt") + "</h3>";
    static const char* const FXN[] = {"Aus", "Zimmer", "Halle", "Kirche", "Echo"};
    h += "<div class='row'>Effekt <select id='fxMode' onchange='fxSend()' style='width:150px'>";
    for (int i = 0; i < 5; i++) h += String("<option value='") + i + "'" + (cfg.fxMode == i ? " selected" : "") + ">" + FXN[i] + "</option>";
    h += "</select> " + infoTip("Zimmer, Halle und Kirche sind Hall mit zunehmender Nachhallzeit; Echo wiederholt den Ton nach etwa 0,35 Sekunden. Aus: kein Effekt") + "</div>";
    h += "<div class='row'>Anteil <input type='range' id='fxWet' min='0' max='100' value='" + String(cfg.fxWet) + "' oninput=\"document.getElementById('fxWetV').textContent=this.value\" onchange='fxSend()' style='width:200px'> <span id='fxWetV'>" + String(cfg.fxWet) + "</span> % " + infoTip("Wie stark der Effekt zum Originalton gemischt wird, 0 bis 100 Prozent") + "</div>";
    h += "<div class='row'>B&auml;sse <input type='range' id='eqBass' min='-12' max='12' value='" + String(cfg.eqBass) + "' oninput=\"document.getElementById('eqBassV').textContent=this.value\" onchange='fxSend()' style='width:200px'> <span id='eqBassV'>" + String(cfg.eqBass) + "</span> dB " + infoTip("Tiefen unter etwa 200 Hz anheben oder absenken; 0 = unver&auml;ndert") + "</div>";
    h += "<div class='row'>H&ouml;hen <input type='range' id='eqTreble' min='-12' max='12' value='" + String(cfg.eqTreble) + "' oninput=\"document.getElementById('eqTrebleV').textContent=this.value\" onchange='fxSend()' style='width:200px'> <span id='eqTrebleV'>" + String(cfg.eqTreble) + "</span> dB " + infoTip("H&ouml;hen ab etwa 4 kHz anheben oder absenken; 0 = unver&auml;ndert") + "</div>";
    static const char* const PANN[] = {"Aus", "links &rarr; rechts", "rechts &rarr; links", "hin und her"};
    h += "<div class='row'>Wandern <select id='fxPan' onchange='fxSend()' style='width:170px'>";
    for (int i = 0; i < 4; i++) h += String("<option value='") + i + "'" + (cfg.panMode == i ? " selected" : "") + ">" + PANN[i] + "</option>";
    h += "</select> " + infoTip("Der Ton wandert beim Abspielen zwischen links und rechts. Zu h&ouml;ren nur mit zwei Verst&auml;rkern im Stereo-Aufbau, ein Modul mischt zu Mono. Bei links &rarr; rechts und rechts &rarr; links bleibt der Ton am Ende stehen, bei hin und her l&auml;uft die Bewegung weiter. Wirkt auf Ansagen und abgespielte Dateien, nie auf Webradio") + "</div>";
    h += "<div class='row'>Dauer <input type='range' id='fxPanSec' min='0.5' max='20' step='0.5' value='" + String(cfg.panDs / 10.0, 1) + "' oninput=\"document.getElementById('fxPanSecV').textContent=this.value\" onchange='fxSend()' style='width:200px'> <span id='fxPanSecV'>" + String(cfg.panDs / 10.0, 1) + "</span> s " + infoTip("Dauer eines Durchgangs von einer Seite zur anderen in Sekunden, 0,5 bis 20") + "</div>";
    h += "<div id='fxResult'></div></div>";
    return h;
}

// Zeile mit der Anzeige, was gerade laeuft, und dem Stopp-Knopf; steht oben in jedem Tab, der Wiedergabe startet.
// Row with the display of what is playing right now and the stop button; at the top of every tab that starts playback.

String nowPlayingRow() {
    return "<div class='row' style='min-height:2.4rem'><strong class='nowplaying' style='color:var(--ok)'></strong></div>";
}

// Belegung von LittleFS und SD-Karte: usedBytes() braucht 45 ms bis mehrere Hundert ms und haelt die Schleife (und den Ton) an; deshalb alle 15 s neu lesen oder nach Aenderungen an Dateien.
// Usage of LittleFS and SD card: usedBytes() takes 45 ms up to several hundred ms and holds up the loop (and the sound); so re-read every 15 s or after file changes.

static unsigned long storageRead = 0;
static size_t fsUsedC = 0, fsTotalC = 0;
static uint64_t sdUsedC = 0, sdTotalC = 0;

void storageInvalidate() {
    storageRead = 0;
}

void storageRefresh() {
    if (storageRead != 0 && millis() - storageRead < 15000UL) return;
    if (fsReady) {
        fsUsedC = LittleFS.usedBytes();
        fsTotalC = LittleFS.totalBytes();
    }
    if (sdReady) {
        sdUsedC = SD.usedBytes();
        sdTotalC = SD.totalBytes();
    }
    storageRead = millis();
    if (storageRead == 0) storageRead = 1;
}

String panelRadio() {
    String h = volumeRow() + nowPlayingRow();
    h += "<details id='radioInfoBox' style='display:none;max-width:500px;margin:0 auto 10px;text-align:left'><summary style='cursor:pointer;color:var(--muted)'>Stream-Info</summary><table id='radioInfo' style='width:100%;margin-top:6px'></table></details>";
    h += "<div class='card' id='favCard' style='max-width:900px'><h3>Favoriten " + infoTip("Eigene Liste mit deinen Lieblingssendern, unabh&auml;ngig von der Senderliste (bis zu 40). Sender lassen sich aus der gespeicherten Senderliste und aus jeder fertigen Liste von GitHub &uuml;bernehmen, direkt anh&ouml;ren und wieder entfernen") + "</h3><small id='favInfo'></small><div id='favList'></div>";
    h += "<div class='row' style='justify-content:flex-start;gap:8px'><button type='button' onclick='favToList()' style='width:auto;padding:8px 14px'>Als Senderliste &uuml;bernehmen</button> " + infoTip("Ersetzt die gespeicherte Senderliste durch die Favoriten") + "</div>";
    h += "<div class='row' style='justify-content:flex-start;gap:8px'><button type='button' onclick=\"location.href='/favorites.txt'\" style='width:auto;padding:8px 14px'>Favoriten speichern</button> " + infoTip("Speichert die Favoriten als Textdatei auf deinem Rechner; sie steht auch im Export der Einstellungen") + " ";
    h += "<button type='button' onclick=\"document.getElementById('favFile').click()\" style='width:auto;padding:8px 14px'>Favoriten laden</button><input type='file' id='favFile' accept='.txt' style='display:none' onchange='loadFavorites(this)'> " + infoTip("Ersetzt die Favoriten durch eine zuvor gespeicherte Datei") + "</div>";
    h += "<div id='favResult'></div></div>";
    h += "<div class='card'><h3>Webradio-URL abspielen</h3><div class='row'>";
    h += "<input id='playUrl' placeholder='https://...' style='width:90%'><button type='button' onclick='playUrlNow()' style='width:150px'>URL abspielen</button> " + infoTip("Adresse eines Webradios oder einer MP3-Datei (http:// oder https://); sie wird jetzt abgespielt, aber nicht gespeichert") + "</div><div id='radioResult'></div></div>";

    // Belegte Plaetze plus der erste freie werden angezeigt; nach dem Speichern erscheint der naechste freie.
    // Used slots plus the first free one are shown; after saving the next free one appears.

    int firstEmpty = -1;
    int used = 0;
    for (int i = 0; i < RADIO_SLOTS; i++) {
        if (cfg.radioUrl[i].isEmpty()) {
            if (firstEmpty < 0) firstEmpty = i;
        } else {
            used++;
        }
    }
    h += "<div class='card' style='max-width:900px'><h3>Gespeicherte Webradios / URLs " + infoTip("Pro Platz: Name (beliebig, auch per REST und MQTT abrufbar), URL (Webradio oder MP3; leer lassen und speichern gibt den Platz frei) und Lautst&auml;rke des Senders (0-100, leer = allgemeine Lautst&auml;rke)") + "</h3><small>" + String(used) + " von " + String(RADIO_SLOTS) + " Pl&auml;tzen belegt</small><form method='POST' action='/save'><input type='hidden' name='sect' value='radio'>";
    for (int i = 0; i < RADIO_SLOTS; i++) {
        if (cfg.radioUrl[i].isEmpty() && i != firstEmpty) continue;
        audioPump();
        String n = String(i + 1);
        h += "<div class='row stationrow' data-n='" + n + "' data-url='" + htmlEsc(cfg.radioUrl[i]) + "'><span style='width:1.6rem;text-align:right;color:var(--muted)'>" + n + "</span>";
        h += "<input name='rn" + n + "' maxlength='" + String(RADIO_NAME_MAX) + "' placeholder='Name' value='" + htmlEsc(cfg.radioName[i]) + "' style='width:150px'>";
        h += "<input name='ru" + n + "' maxlength='" + String(RADIO_URL_MAX) + "' placeholder='http://...' value='" + htmlEsc(cfg.radioUrl[i]) + "' style='width:300px'>";
        h += "<input type='number' name='rv" + n + "' min='0' max='" + String(VOLUME_MAX) + "' placeholder='Std' value='" + (cfg.radioVol[i] >= 0 ? String(cfg.radioVol[i]) : String()) + "' style='width:64px'>";
        String off = cfg.radioUrl[i].isEmpty() ? " disabled" : "";
        h += "<button type='button' class='copy-btn' style='position:static;margin:2px' title='Nach oben schieben (speichert sofort)' onclick='moveStation(" + n + ",-1)'" + off + ">&#9650;</button>";
        h += "<button type='button' class='copy-btn' style='position:static;margin:2px' title='Nach unten schieben (speichert sofort)' onclick='moveStation(" + n + ",1)'" + off + ">&#9660;</button>";
        h += "<button type='button' class='copy-btn' style='position:static;margin:2px' title='Zu den Favoriten hinzuf&uuml;gen' onclick='favAddStation(" + n + ")'" + off + ">+</button>";
        h += "<button type='button' class='playbtn' onclick='playStation(" + n + ")' title='Abspielen' style='width:auto;padding:8px 14px'" + off + ">&#9654;</button>";
        h += "<button type='button' class='copy-btn' style='position:static;margin:2px' title='Aufruf per REST und MQTT anzeigen' onclick='stationCall(" + n + ",this)'" + off + ">API</button>";
        h += "<button type='button' class='copy-btn' style='position:static;margin:2px' title='Platz l&ouml;schen (Name und URL); die folgenden Pl&auml;tze r&uuml;cken auf' onclick='delStation(" + n + ")'" + off + ">&#10006;</button></div>";
    }
    h += "<small>Das Feld rechts neben der URL ist die Lautst&auml;rke des Senders (0-100, leer = allgemeine Lautst&auml;rke). Speichern, bevor du &#9654; dr&uuml;ckst. &#9650;&#9660; verschieben den Sender und speichern sofort. Der URL-Knopf kopiert den REST-Aufruf mit Beispielwerten f&uuml;r alle Parameter, zum Beispiel <code>/api/station?n=Platz&amp;vol=60</code>; auch der Name geht (<code>?name=...</code>).</small>";
    h += "<button type='submit'>Speichern</button><div id='stResult'></div></form>";
    h += "<div style='margin-top:18px;padding-top:12px;border-top:1px solid var(--panel-border)'><h3 style='margin:0 0 6px'>Senderlisten</h3>";
    h += "<div class='row' style='justify-content:flex-start;gap:8px'><span style='min-width:110px;text-align:left'>Eigene Liste</span><button type='button' onclick=\"location.href='/stations.txt'\" style='width:auto;padding:8px 14px'>Liste speichern</button> " + infoTip("Speichert die Senderliste (Name, URL, Lautst&auml;rke) als Textdatei auf deinem Rechner") + " ";
    h += "<button type='button' onclick=\"document.getElementById('stFile').click()\" style='width:auto;padding:8px 14px'>Liste laden</button><input type='file' id='stFile' accept='.txt' style='display:none' onchange='loadStations(this)'> " + infoTip("Ersetzt die gespeicherte Senderliste durch eine zuvor gespeicherte Datei") + "</div>";
    h += "<div class='row' style='justify-content:flex-start;gap:8px'><span style='min-width:110px;text-align:left'>Fertige Liste</span><select id='stList' style='width:auto'><option>aac-auswahl</option><option>mp3-auswahl</option><option>rock</option><option>entspannung</option><option>schlager</option><option>country</option><option>folk</option><option>jazz</option><option>klassik</option><option>pop-charts</option><option>jahrzehnte</option><option>dance</option><option>hiphop</option><option>irland</option><option>usa</option><option>australien</option><option>grossbritannien</option><option>frankreich</option></select><button type='button' onclick='listFetch()' style='width:auto;padding:8px 14px'>Von GitHub laden</button> " + infoTip("L&auml;dt eine fertige Senderliste aus dem Ordner stations des Projekts auf GitHub und ersetzt die gespeicherte Liste; das Ger&auml;t braucht dazu Internet") + "</div>";
    h += "<div class='row' style='justify-content:flex-start;gap:8px'><span style='min-width:110px;text-align:left'>Sender meines Landes</span><select id='rbCountry' style='width:auto'></select><select id='rbGenre' style='width:auto'><option value=''>Alle Genres</option><option>pop</option><option>rock</option><option>jazz</option><option>classical</option><option>country</option><option>folk</option><option>electronic</option><option>dance</option><option>hip hop</option><option>oldies</option><option>80s</option><option>90s</option><option>schlager</option><option>lounge</option><option>reggae</option><option>latin</option><option>world</option><option>metal</option><option>blues</option><option>soul</option><option value='christmas'>Weihnachten</option></select><button type='button' onclick='rbLoad()' style='width:auto;padding:8px 14px'>Von radio-browser laden</button> " + infoTip("Holt die beliebtesten Sender des gew&auml;hlten Landes (optional eines Genres) aus dem offenen Verzeichnis radio-browser.info und ersetzt die gespeicherte Senderliste; nur Sender mit MP3 oder AAC, die zuletzt erreichbar waren, h&ouml;chstens 30. Der Browser ruft das Verzeichnis ab, das Ger&auml;t braucht dazu nichts. Die Favoriten stehen danach vorn") + "</div><div id='stListResult'></div></div></div>";
    return h;
}

String panelSd() {
    String h = volumeRow() + nowPlayingRow();
    h += "<div class='card' style='max-width:900px'><h3>SD-Karte</h3><small id='sdInfo'>Lade &hellip;</small><div id='sdMem'></div><div id='sdPath' style='margin:6px 0;color:var(--muted)'></div><div id='sdList'></div>";
    h += "<div class='row'><input type='file' id='sdUpFile' multiple accept='.mp3' style='width:55%'><button type='button' onclick='sdUploadNow()' style='width:auto;padding:8px 14px'>Hochladen</button> " + infoTip("Eine oder mehrere MP3-Dateien w&auml;hlen; sie werden nacheinander in den gezeigten Ordner der Karte hochgeladen") + "</div>";
    h += "<div class='row'><button type='button' onclick='sdLoad(sdCur)' style='width:auto;padding:8px 14px'>Aktualisieren</button><button type='button' onclick='sdMkdir()' style='width:auto;padding:8px 14px'>Neuer Ordner</button><button type='button' onclick='sdRemount()' style='width:auto;padding:8px 14px'>Neu einbinden</button> <label style='display:inline-flex;align-items:center;gap:4px'><input type='checkbox' id='sdLoop'> Endlos</label> " + infoTip("Aktualisieren: liest den gezeigten Ordner neu. Neuer Ordner: legt einen Ordner im gezeigten Ordner an. Neu einbinden: bindet die Karte neu ein, zum Beispiel nach dem Einstecken. Endlos: nach der letzten Datei eines Ordners beginnt eine neue Runde. Zufall (Knopf am Ordner): jede Datei kommt je Sitzung einmal, die Reihenfolge ist jedes Mal eine andere und beginnt nie mit der Datei der letzten Sitzung") + "</div><div id='sdResult'></div></div>";
    return h;
}

String panelPins() {
    String h = "<div class='card' style='max-width:900px'><div style='display:flex;justify-content:space-between;align-items:center;gap:10px'><h3 style='margin:0'>Eing&auml;nge (Pull-up)</h3><button type='button' id='pinSave' style='width:auto;padding:8px 18px'>Speichern</button></div>";
    h += "<p>Alle freien Pins liegen mit Pull-up auf High. Bekommt ein Pin Kontakt nach GND (zum Beispiel durch eine Taste), spielt das Ger&auml;t die gew&auml;hlte Ansage, MP3-Datei oder den gew&auml;hlten Webradio-Sender. Nicht angezeigt werden die Pins von Verst&auml;rker und SD-Karte, die Strapping-Pins und die Status-LED. " + infoTip("Aktion: Ansage = Text, der &uuml;ber VoiceRSS gesprochen wird. MP3-Datei = Dateiname aus dem Tab MP3 (Flash), sd:/Pfad.mp3 oder sd:/Ordner/ von der SD-Karte oder eine URL (http:// oder https://). Webradio = gespeicherter Sender, Name oder Platznummer aus dem Tab Webradio. Radio starten = spielt den zuletzt gespielten Sender (sonst den ersten gespeicherten), Sender vor/zur&uuml;ck = n&auml;chster/vorheriger gespeicherter Sender, Lauter/Leiser = Schrittweite im Feld Lautst&auml;rke (Standard 5), Stumm schaltet um, Stopp beendet die Wiedergabe. Die Lautst&auml;rke ist optional (0-100, leer = allgemeine). Der Pin muss etwa 40 ms auf GND bleiben; ausgel&ouml;st wird einmal je Tastendruck") + "</p>";
    h += "<table id='pinTable' style='width:100%'></table><div id='pinResult'></div></div>";
    return h;
}

String panelMp3() {
    String h = volumeRow() + nowPlayingRow();
    h += "<div class='card' style='max-width:900px'><h3>Dateien im Ger&auml;t</h3><div id='fsMem'></div><div id='fileList'>Lade &hellip;</div><hr>";
    h += "<div class='row'><input type='file' id='upFile' multiple accept='.mp3' style='width:90%'><button type='button' onclick='uploadNow()' style='width:150px'>Hochladen</button> " + infoTip("Eine oder mehrere MP3-Dateien vom Rechner w&auml;hlen; sie werden nacheinander in den Speicher des Ger&auml;ts geladen") + "</div>";
    h += "<div id='upResult'></div></div>";
    return h;
}

// Auswahlfeld fuer einen Pin: alle erlaubten GPIOs des ESP32-S3; ein gespeicherter, nicht erlaubter Wert bleibt sichtbar.
// Select field for a pin: all allowed GPIOs of the ESP32-S3; a stored value that is not allowed stays visible.

String pinSelect(const char* name, int value) {
    String s = String("<select class='pinsel' name='") + name + "' onchange='checkPins()' style='width:130px'>";
    bool found = false;
    for (int p = 0; p <= 48; p++) {
        if (!pinAllowed(p)) continue;
        if (p == value) found = true;
        s += "<option value='" + String(p) + "'" + (p == value ? " selected" : "") + ">GPIO " + String(p) + "</option>";
    }
    if (!found) s += "<option value='" + String(value) + "' selected>GPIO " + String(value) + " (nicht erlaubt)</option>";
    return s + "</select>";
}

String pinRow(const char* label, const char* name, int value, const char* title) {
    return String("<div class='row pinrow'><span class='pinlabel'>") + label + "</span>" + pinSelect(name, value) + " " + infoTip(title) + "</div>";
}

// Der Tab Audio fasst alles zusammen, was Ton und Sprache betrifft, in getrennten Karten; ein Speichern gilt fuer alle.
// The Audio tab gathers everything about sound and speech in separate cards; one save applies to all.

String panelAudio() {
    String h = "<form method='POST' action='/save'><input type='hidden' name='sect' value='audio'>";
    h += "<div class='card wide'><h3>Anschl&uuml;sse</h3>";
    h += "<div class='sub'><h4>Verst&auml;rker (I2S, MAX98357A)</h4>";
    h += pinRow("DIN (Daten)", "din", cfg.din, "GPIO f&uuml;r die Daten (DIN) zum Verst&auml;rker; wirkt nach einem Neustart");
    h += pinRow("BCLK (Bit-Takt)", "bclk", cfg.bclk, "GPIO f&uuml;r den Bit-Takt (BCLK) des Verst&auml;rkers; wirkt nach einem Neustart");
    h += pinRow("LRC (Wort-Takt)", "lrc", cfg.lrc, "GPIO f&uuml;r den Wort-Takt (LRC/WS) des Verst&auml;rkers; wirkt nach einem Neustart");
    h += "<small>&Auml;nderungen an diesen Pins wirken nach einem Neustart.</small></div>";
    h += "<div class='sub'><h4>SD-Karte (SPI)</h4>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' name='sdon' value='1'" + String(cfg.sdOn ? " checked" : "") + " style='width:auto;margin:0;'>SD-Karte verwenden</label> " + infoTip("SD-Karte im SPI-Modus verwenden; ohne Karte l&auml;uft alles andere weiter") + "</div>";
    h += pinRow("MISO (Daten von der Karte)", "sdmiso", cfg.sdMiso, "Daten von der Karte (MISO/DO); &Auml;nderungen wirken sofort");
    h += pinRow("SCK (Takt)", "sdsck", cfg.sdSck, "Takt (CLK) der SD-Karte; &Auml;nderungen wirken sofort");
    h += pinRow("MOSI (Daten zur Karte)", "sdmosi", cfg.sdMosi, "Daten zur Karte (MOSI/DI); &Auml;nderungen wirken sofort");
    h += pinRow("CS (Chip-Select)", "sdcs", cfg.sdCs, "Chip-Select der SD-Karte; &Auml;nderungen wirken sofort");
    h += "<small>&Auml;nderungen an den SD-Pins wirken sofort, die Karte wird neu eingebunden.</small></div>";
    h += "<small id='pinWarn' class='pinwarn'></small>";
    h += "<small>Erlaubte Pins am ESP32-S3: 1-18, 21, 33-42, 47, 48. Jeder Pin darf nur einmal vergeben sein; sonst werden die Pins nicht gespeichert.</small></div>";
    h += "<div class='card wide'><h3>Lautst&auml;rke</h3>";
    h += "<div class='row'>Standard-Lautst&auml;rke (0-" + String(VOLUME_MAX) + ") " + infoTip("Lautst&auml;rke, die nach dem Start gilt und wenn nichts anderes eingestellt ist") + " <input type='number' name='vol' min='0' max='" + String(VOLUME_MAX) + "' value='" + String(cfg.vol) + "' style='width:90px'></div>";
    h += "<div class='row'>Lautst&auml;rke &auml;ndern (ms) " + infoTip("Dauer, in der eine ge&auml;nderte Lautst&auml;rke (Regler, REST, MQTT) bei laufendem Ton zum neuen Wert wandert; 0 = sofort. Per REST und MQTT l&auml;sst sich die Dauer je Aufruf mit ms angeben") + " <input type='number' name='vramp' min='0' max='" + String(VOLUME_RAMP_MAX_MS) + "' step='100' value='" + String(cfg.volRampMs) + "' style='width:90px'></div>";
    h += "</div>";
    h += "<div class='card wide'><h3>&Uuml;berblenden und Mischen</h3>";
    h += "<div class='sub'><h4>Webradio ein- und ausblenden</h4>";
    h += "<div class='row'>Radio aus-/einblenden (ms) " + infoTip("Dauer, in der ein laufendes Webradio vor einer Ansage oder MP3-Datei auf Lautst&auml;rke 0 ausgeblendet und nach der Fortsetzung wieder eingeblendet wird; auch das Absenken beim Mischen nutzt diese Zeit; 0 = sofort") + " <input type='number' name='fade' min='0' max='" + String(FADE_MAX_MS) + "' step='100' value='" + String(cfg.fadeMs) + "' style='width:90px'></div>";
    h += "<div class='row'>Radio Start/Stopp/Wechsel (ms) " + infoTip("Dauer des Einblendens beim Start eines Webradios, des Ausblendens beim Stopp und beider beim Senderwechsel; 0 = sofort") + " <input type='number' name='swfade' min='0' max='" + String(FADE_MAX_MS) + "' step='100' value='" + String(cfg.switchFadeMs) + "' style='width:90px'></div>";
    h += "</div><div class='sub'><h4>Ansagen &uuml;ber dem Radio</h4>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' name='mix' value='1'" + String(cfg.mixAnn ? " checked" : "") + " style='width:auto;margin:0;'>Radio unter Ansagen weiterlaufen lassen</label> " + infoTip("Ansagen (und bei Webradio auch MP3-Dateien) werden leise &uuml;ber das laufende Webradio oder eine laufende MP3-Datei gelegt, die ohne Unterbrechung weiterl&auml;uft. Aus: das Radio stoppt f&uuml;r die Ansage und wird danach neu verbunden; eine MP3-Datei stoppt ebenfalls") + " Radio dabei auf <input type='number' name='duck' min='0' max='100' value='" + String(cfg.duckPct) + "' style='width:64px'> % " + infoTip("Lautst&auml;rke des Radios w&auml;hrend der Ansage in Prozent der eingestellten Lautst&auml;rke") + "</div>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' name='loud' value='1'" + String(cfg.loudNorm ? " checked" : "") + " style='width:auto;margin:0;'>MP3-Lautst&auml;rke angleichen</label> " + infoTip("Beim ersten Abspielen einer MP3-Datei misst das Ger&auml;t im Hintergrund ihre Lautst&auml;rke und gleicht sie auf einen einheitlichen Pegel an; der Ausgleich wird gespeichert, die Datei selbst bleibt unver&auml;ndert. W&auml;hrend der Messung (einige Sekunden bis eine Minute) l&auml;uft die Datei noch unver&auml;ndert und wird dann sanft angepasst. Ansagen und Radio bleiben unver&auml;ndert") + "</div>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' name='agc' value='1'" + String(cfg.radioAgc ? " checked" : "") + " style='width:auto;margin:0;'>Webradio-Lautst&auml;rke angleichen</label> " + infoTip("Misst laufend den Pegel des Webradios und f&uuml;hrt die Verst&auml;rkung langsam auf den Zielpegel nach (hoch in etwa 5 s, runter in etwa 1 s, h&ouml;chstens 12 dB), so klingen laute und leise Sender &auml;hnlich; Spitzen bleiben unter -1 dBFS. Wirkt nur auf Webradio, nicht auf Ansagen und Dateien. Die Lautst&auml;rke je Sender in der Senderliste bleibt zus&auml;tzlich wirksam") + "</div>";
    h += "<div class='row'>Zielpegel Webradio (dBFS) " + infoTip("Mittlerer Pegel, auf den die Angleichung zielt: -30 (leise) bis -10 (laut); -18 ist ein guter Anfang. Gilt nur mit dem Haken oben") + " <input type='number' name='agcdb' min='-30' max='-10' value='" + String(cfg.agcDb) + "' style='width:70px'></div>";
    h += "<div class='row'>Vorpuffer Webradio (Sekunden) " + infoTip("Das Radio beginnt erst zu spielen, wenn so viele Sekunden Ton im Puffer liegen. Ein gr&ouml;&szlig;erer Wert &uuml;berbr&uuml;ckt kurze Aussetzer des Streams (Meldung slow stream), der Ton kommt nach dem Start eines Senders aber entsprechend später. 0 bis 30, Standard 5") + " <input type='number' name='prebuf' min='0' max='30' value='" + String(cfg.prebufSec) + "' style='width:70px'></div>";
    h += "</div><div class='sub'><h4>Titelregel</h4>";
    h += "<div class='row'>Titelregel: Titel enth&auml;lt " + infoTip("Stichworte der Titelregel:&#10;&#8226; Mehrere Stichworte mit Komma oder Semikolon trennen.&#10;&#8226; Gro&szlig;-/Kleinschreibung ist egal; es gen&uuml;gt, wenn der Titel das Stichwort enth&auml;lt.&#10;&#8226; Mit =Wert (0-100) bekommt ein Stichwort eine eigene Lautst&auml;rke, zum Beispiel: Cambodia=90, Thunder&#10;&#8226; Leer = Regel aus") + " <input name='tmatch' maxlength='120' value='" + htmlEsc(cfg.titleMatch) + "' placeholder='z. B. Cambodia, Thunder=90' style='width:280px'> Lautst&auml;rke <input type='number' name='tvol' min='0' max='" + String(VOLUME_MAX) + "' value='" + String(cfg.titleVol) + "' style='width:64px'> " + infoTip("Lautst&auml;rke (0-100) f&uuml;r Stichworte ohne eigenen Wert; sie gilt, solange der Titel l&auml;uft, danach wieder die vorherige") + " h&ouml;chstens <input type='number' name='tmax' min='0' max='3600' value='" + String(cfg.titleMaxS) + "' style='width:70px'> s " + infoTip("Ein Sender meldet das Ende eines Titels nicht. Mit einem Wert gr&ouml;&szlig;er als 0 endet die Titelregel nach so vielen Sekunden (zum Beispiel 210 f&uuml;r einen Titel von 3:30), damit Werbung nach dem Titel nicht laut bleibt; 0 = bis zum n&auml;chsten Titel") + "</div>";
    h += "</div></div>";
    h += "<div class='card wide'><h3>Start</h3>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' name='autostart' value='1'" + String(cfg.autoStart ? " checked" : "") + " style='width:auto;margin:0;'>Beim Start Sender 1 abspielen</label> " + infoTip("Spielt nach dem Start nach einigen Sekunden Sender 1 der Liste ab, sobald das WLAN steht und der Stream antwortet. Ausgeschaltet bleibt das Ger&auml;t nach dem Start stumm") + "</div>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' name='btone' value='1'" + String(cfg.bootTone ? " checked" : "") + " style='width:auto;margin:0;'>Kurzer Ton beim Start</label> " + infoTip("Beim Einschalten und nach einem Neustart &uuml;ber die Weboberfl&auml;che spielt das Ger&auml;t einen kurzen Ton (&bdquo;buub&ldquo;) immer mit Lautst&auml;rke 50, unabh&auml;ngig von der allgemeinen Lautst&auml;rke. Nach einem Neustart per MQTT, nach einem Absturz und im abgesicherten Modus bleibt er aus") + "</div>";
    h += "<small>Aus (Standard): Das Ger&auml;t startet stumm. An: Nach dem Start spielt es nach einigen Sekunden Sender 1 der Liste im Tab Webradio, sobald der Stream antwortet (bis zu 10 Versuche im Abstand von 6 s).</small><br>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' name='resume' value='1'" + String(cfg.resumeLast ? " checked" : "") + " style='width:auto;margin:0;'>Zuletzt gespielten Sender nach einem Neustart fortsetzen</label> " + infoTip("Merkt sich den laufenden Sender mit seiner Lautst&auml;rke und spielt ihn nach einem Neustart oder Stromausfall wieder ab; ein Stopp l&ouml;scht den Merker") + "</div>";
    h += "<small>Das Ger&auml;t merkt sich Sender und Lautst&auml;rke (erst wenn die Lautst&auml;rke 3 s unver&auml;ndert ist). Nach einem Neustart spielt es ihn wieder ab, mit derselben Lautst&auml;rke; ein Stopp l&ouml;scht den Merker, dann startet das Ger&auml;t stumm. Hat dieser Haken Vorrang vor &bdquo;Beim Start Sender 1 abspielen&ldquo;.</small>";
    h += "</div>";
    h += "<div class='card wide'><h3>Sprachausgabe (VoiceRSS)</h3>";
    h += "<div class='row'><input type='text' name='vkey' maxlength='64' placeholder='API-Schl&uuml;ssel' value='" + htmlEsc(cfg.vkey) + "' autocomplete='off' style='width:260px'> " + infoTip("API-Schl&uuml;ssel von voicerss.org; ein leeres Feld l&ouml;scht ihn") + "</div>";
    h += "<small>Der Schl&uuml;ssel wird angezeigt; ein leeres Feld l&ouml;scht ihn. Er steht nicht im Export der Einstellungen und muss auf einem neuen Ger&auml;t neu eingetragen werden. Kostenloser Schl&uuml;ssel: voicerss.org</small>";
    h += "<div class='row'><select name='vlang' id='cfgLang' onchange=\"fillVoiceSel('cfgVoice',this.value,false)\" style='width:260px'>" + selectOptions(LANG_VALUES, LANG_LABELS, LANG_COUNT, cfg.vlang) + "</select> " + infoTip("Standardsprache f&uuml;r Ansagen") + "</div>";
    h += "<div class='row'><select name='vvoice' id='cfgVoice' onchange='voiceChosen(this)' style='width:260px'><option value=''>Standard (VoiceRSS)</option>" + (cfg.vvoice.length() > 0 ? "<option value='" + htmlEsc(cfg.vvoice) + "' selected>" + htmlEsc(cfg.vvoice) + "</option>" : String()) + "</select> " + infoTip("Standardstimme f&uuml;r Ansagen; Standard = Standardstimme der Sprache") + "</div>";
    h += "<div class='row'>Tempo (-10 bis 10): " + infoTip("Sprechtempo: -10 = sehr langsam, 0 = normal, 10 = sehr schnell") + " <input type='number' name='vrate' min='-10' max='10' value='" + String(cfg.vrate) + "' style='width:90px'></div>";
    h += "<div class='row'><select name='vfmt' style='width:260px'>" + selectOptions(FMT_VALUES, FMT_LABELS, 4, cfg.vfmt) + "</select> " + infoTip("Audioformat der Sprachdatei: kleiner = schneller geladen, gr&ouml;&szlig;er = bessere Qualit&auml;t") + "</div>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' name='ttsc' value='1'" + String(cfg.ttsCache ? " checked" : "") + " style='width:auto;margin:0;'>Ansagen auf der SD-Karte zwischenspeichern</label> " + infoTip("Ein einmal von VoiceRSS geholter Text wird als MP3 im Ordner /tts der SD-Karte abgelegt; der Dateiname beginnt mit einem Hinweis auf den Text, zum Beispiel Achtung_auf_Gleis_3_3fa9c2e1.mp3. Derselbe Text mit gleicher Sprache, Stimme, Tempo und gleichem Format wird danach von der Karte gespielt, ohne Internet und ohne VoiceRSS-Anfrage. Es bleiben h&ouml;chstens 500 Dateien, die &auml;ltesten werden gel&ouml;scht. Ohne Karte l&auml;uft alles wie bisher") + "</div>";
    h += "<div class='row'><button type='button' onclick='ttsClear()' style='width:auto;padding:8px 14px'>Zwischenspeicher leeren</button> <span id='ttsInfo'></span> <span id='ttsResult'></span> " + infoTip("L&ouml;scht alle zwischengespeicherten Ansagen von der SD-Karte (Ordner /tts); sie werden bei Bedarf neu von VoiceRSS geholt") + "</div>";
    h += "<div class='row'><button type='button' onclick='voiceTest()' style='width:auto;padding:8px 14px'>Stimme testen</button> " + infoTip("Spricht einen kurzen Beispielsatz in der gew&auml;hlten Sprache, Stimme und mit dem eingestellten Tempo, auch ohne vorher zu speichern. Der API-Schl&uuml;ssel und das Audioformat m&uuml;ssen dazu gespeichert sein") + "</div><div id='voiceTestResult'></div>";
    h += "</div>";
    h += "<div style='text-align:center'><button type='submit'>Speichern</button></div></form>";
    return h;
}

// Eine Zeile der Topic-Tabelle: Topic mit Kopierknopf, Art (Befehl = senden, Meldung = lesen), Nutzlast, Beispiele.
// One row of the topic table: topic with copy button, kind (command = send, message = read), payload, examples.

String mqttRow(const String& base, const char* suffix, bool command, const char* payloadText, const char* const* examples, int exampleCount) {
    String topic = base + suffix;
    String h = "<tr><td><code>" + htmlEsc(topic) + "</code><br><button type='button' class='copy-btn' style='position:static;margin:4px 0 0' data-copy='" + htmlEsc(topic) + "' onclick='copyText(this.getAttribute(\"data-copy\"),this)' title='Topic kopieren'>Kopieren</button></td>";
    h += String("<td><span class='kind ") + (command ? "cmd'>senden" : "msg'>lesen") + "</span></td><td>" + payloadText + "</td><td>";
    for (int i = 0; i < exampleCount; i++) h += "<code class='ex'>" + htmlEsc(examples[i]) + "</code>";
    return h + "</td></tr>";
}

String panelMqtt() {
    String base = mqttBaseTopic();
    String h = "<div class='card mqtt' style='max-width:1000px'><h3>MQTT</h3><form method='POST' action='/save'><input type='hidden' name='sect' value='mqtt'>";
    h += "<div class='row' style='justify-content:flex-start;gap:6px 18px'>";
    h += "<span style='display:inline-flex;align-items:center;gap:6px'><label for='mq_srv' style='white-space:nowrap'>Broker " + infoTip("Adresse des MQTT-Brokers; leer = MQTT aus") + "</label><input id='mq_srv' name='mq_srv' placeholder='z. B. 192.168.0.70 (leer = MQTT aus)' value='" + htmlEsc(cfg.mqttServer) + "' style='width:min(100%,300px);margin:4px 0'></span>";
    h += "<span style='display:inline-flex;align-items:center;gap:6px'><label for='mq_port' style='white-space:nowrap'>Port " + infoTip("Port des Brokers, meist 1883") + "</label><input id='mq_port' type='number' name='mq_port' min='1' max='65535' value='" + String(cfg.mqttPort) + "' style='width:100px;margin:4px 0'></span></div>";
    h += "<div class='row' style='justify-content:flex-start;gap:6px 18px'>";
    h += "<span style='display:inline-flex;align-items:center;gap:6px'><label for='mq_user' style='white-space:nowrap'>Benutzer " + infoTip("Benutzername f&uuml;r den MQTT-Broker (optional); leer = ohne Anmeldung") + "</label><input id='mq_user' name='mq_user' autocomplete='off' placeholder='optional' value='" + htmlEsc(cfg.mqttUser) + "' style='width:min(100%,200px);margin:4px 0'></span>";
    h += "<span style='display:inline-flex;align-items:center;gap:6px'><label for='mq_pass' style='white-space:nowrap'>Passwort " + infoTip("Passwort f&uuml;r den MQTT-Broker (optional); es wird nicht angezeigt. Leer lassen, um das gespeicherte zu behalten; ohne Benutzer wird es gel&ouml;scht") + "</label><input id='mq_pass' name='mq_pass' type='password' autocomplete='new-password' placeholder='" + String(cfg.mqttPass.length() > 0 ? "gespeichert (leer lassen = behalten)" : "optional") + "' value='' style='width:min(100%,260px);margin:4px 0'></span></div>";
    h += "<div class='row' style='justify-content:flex-start'><span style='display:inline-flex;align-items:center;gap:6px;flex-wrap:wrap'><label for='mq_base' style='white-space:nowrap'>Basis-Topic " + infoTip("Basis-Topic; darunter liegen say, play, url, file, station, stop, volume, restart, status") + "</label><input id='mq_base' name='mq_base' placeholder='" + htmlEsc(String(PROJECT_NAME) + "/" + cfg.host) + "' value='" + htmlEsc(cfg.mqttBase) + "' style='width:min(100%,420px);margin:4px 0'></span></div>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' name='mq_ha' value='1'" + String(cfg.haDisc ? " checked" : "") + " style='width:auto;margin:0;'>Home Assistant Discovery</label> " + infoTip("Meldet das Ger&auml;t bei Home Assistant an (MQTT Discovery): Status, Titel, Lautst&auml;rke, Ansage, Stopp und Senderauswahl erscheinen dort von selbst. Nur n&ouml;tig, wenn du Home Assistant benutzt") + "</div>";
    int grpVisible = 1;
    for (int i = 0; i < 5; i++) {
        if (!cfg.mqttGroup[i].isEmpty()) grpVisible = i + 2;
    }
    if (grpVisible > 5) grpVisible = 5;
    for (int i = 1; i <= 5; i++) {
        String n = String(i);
        h += "<div id='grpRow" + n + "' class='row' style='justify-content:flex-start;" + String(i > grpVisible ? "display:none" : "") + "'><span style='display:inline-flex;align-items:center;gap:6px;flex-wrap:wrap'><label for='mq_g" + n + "' style='white-space:nowrap'>Gruppen-Topic " + n + " " + infoTip("Zus&auml;tzliches Abo, um mehrere Ger&auml;te mit einem Befehl anzusprechen: Das Ger&auml;t nimmt unter diesem Topic dieselben Befehle an wie unter dem Basis-Topic (say, play, url, file, station, list, stop, volume, restart), zum Beispiel netspeaker/all/stop. Bis zu 5, leere Felder werden &uuml;bersprungen") + "</label><input id='mq_g" + n + "' name='mq_g" + n + "' placeholder='z. B. netspeaker/all' value='" + htmlEsc(cfg.mqttGroup[i - 1]) + "' oninput='grpGrow(" + n + ")' style='width:min(100%,420px);margin:4px 0'></span></div>";
    }
    h += "<p><small style='font-size:.9rem'>Leer = <code>netspeaker/&lt;Hostname&gt;</code>. Bereits gespeicherte Topics folgen einem neuen Hostnamen nicht automatisch. Status: <strong>" + String(mqttClient.connected() ? "verbunden" : (cfg.mqttServer.isEmpty() ? "aus" : "nicht verbunden")) + "</strong>.</small></p>";
    h += "<button type='submit' style='width:auto;padding:10px 28px'>Speichern</button></form>";
    h += "<h3 style='margin-top:1.4rem'>Topics</h3><p>Befehle sendest du an die Topics mit <span class='kind cmd'>senden</span>, Meldungen liest du von denen mit <span class='kind msg'>lesen</span> (die meisten sind <em>retained</em>, du bekommst den letzten Stand sofort beim Abonnieren). Als Nutzlast geht Text oder JSON.</p>";
    h += "<table><tr><th>Topic</th><th>Art</th><th>Nutzlast</th><th>Beispiele</th></tr>";
    static const char* const exSay[] = {"Das Abendessen ist fertig", "{\"text\":\"Es klingelt an der T\xC3\xBCr\",\"lang\":\"de-de\",\"voice\":\"Hanna\",\"vol\":15}"};
    static const char* const exPlay[] = {"https://dispatcher.rndfnk.com/br/br3/live/mp3/mid", "klingel.mp3", "{\"file\":\"klingel.mp3\",\"vol\":18}"};
    static const char* const exUrl[] = {"https://dispatcher.rndfnk.com/br/br3/live/mp3/mid"};
    static const char* const exFile[] = {"klingel.mp3"};
    static const char* const exStation[] = {"2", "BR3", "{\"name\":\"BR3\",\"vol\":8}"};
    static const char* const exStop[] = {"(leer)"};
    static const char* const exVol[] = {"50", "{\"v\":60,\"ms\":3000}"};
    static const char* const exList[] = {"(leer)"};
    static const char* const exRestart[] = {"(leer)"};
    static const char* const exStatus[] = {"idle", "playing", "error: File not found: /mp3/klingel.mp3"};
    static const char* const exNow[] = {"BR3 - K\xC3\xBCnstler - Titel", "klingel.mp3", "Ansage"};
    static const char* const exStations[] = {"{\"stations\":[{\"n\":1,\"name\":\"BR3\",\"url\":\"https://...\",\"vol\":null}]}"};
    static const char* const exFavorites[] = {"{\"max\":40,\"favorites\":[{\"n\":1,\"name\":\"BR3\",\"url\":\"https://...\"}]}"};
    static const char* const exVolState[] = {"12"};
    static const char* const exAvail[] = {"online", "offline"};
    h += mqttRow(base, "/say", true, "Text, der angesagt wird. Oder JSON mit <code>text</code> und optional <code>lang</code>, <code>voice</code>, <code>rate</code>, <code>vol</code>, <code>save</code>, <code>fx</code> (0 = ohne Klangeffekt).", exSay, 2);
    h += mqttRow(base, "/play", true, "URL (Webradio, MP3) <em>oder</em> Dateiname aus dem Tab MP3 (Flash) oder <code>sd:/Pfad.mp3</code> von der SD-Karte. Das Ger&auml;t erkennt selbst, was es ist. JSON: <code>url</code> oder <code>file</code>, optional <code>vol</code>; bei einem Ordner (<code>sd:/Pfad/</code>) auch <code>shuffle</code> (zuf&auml;llige Reihenfolge) und <code>loop</code> (endlos), z. B. <code>{&quot;file&quot;:&quot;sd:/Musik/&quot;,&quot;shuffle&quot;:1,&quot;loop&quot;:1}</code>.", exPlay, 3);
    h += mqttRow(base, "/url", true, "URL (http:// oder https://). JSON: <code>url</code>, optional <code>vol</code>.", exUrl, 1);
    h += mqttRow(base, "/file", true, "Dateiname einer hochgeladenen Datei, <code>sd:/Pfad.mp3</code> oder ein Ordner <code>sd:/Ordner/</code>. JSON: <code>file</code>, optional <code>vol</code>, <code>shuffle</code> und <code>loop</code>. Stereo-Position (nur im Stereo-Aufbau h&ouml;rbar): optional <code>pan</code> (<code>off</code>, <code>left</code> links, <code>right</code> rechts, <code>lr</code> links nach rechts, <code>rl</code> rechts nach links, <code>pp</code> hin und her) und <code>pansec</code> (Dauer eines Durchgangs in Sekunden); gilt auch f&uuml;r <code>/play</code> und <code>/api/file</code>. Ohne Angabe gilt die Einstellung im Tab Ansage.", exFile, 1);
    h += mqttRow(base, "/station", true, "Gespeicherter Sender: Platznummer 1-30 oder Name. JSON: <code>n</code> oder <code>name</code>, optional <code>vol</code>.", exStation, 3);
    h += mqttRow(base, "/stop", true, "Keine Nutzlast: beendet die Wiedergabe, auch ein Webradio.", exStop, 1);
    h += mqttRow(base, "/volume", true, "Allgemeine Lautst&auml;rke 0 bis 100 (wird gespeichert); sie wandert sanft zum neuen Wert. Als JSON l&auml;sst sich die Dauer je Aufruf in Millisekunden angeben: <code>{\"v\":60,\"ms\":3000}</code>.", exVol, 2);
    h += mqttRow(base, "/list", true, "Keine Nutzlast: sendet Senderliste und Favoriten erneut.", exList, 1);
    h += mqttRow(base, "/restart", true, "Keine Nutzlast: startet das Ger&auml;t neu. <strong>Nicht retained senden</strong>, sonst wird ein gespeicherter Befehl nach dem Verbinden ignoriert.", exRestart, 1);
    h += mqttRow(base, "/status", false, "Zustand: <code>idle</code>, <code>loading</code>, <code>playing</code> oder <code>error: ...</code>.", exStatus, 3);
    h += mqttRow(base, "/now", false, "Was gerade l&auml;uft: Sendername und Titel, Dateiname oder &quot;Ansage&quot;; leer, wenn nichts l&auml;uft.", exNow, 3);
    h += mqttRow(base, "/stations", false, "Liste der gespeicherten Sender als JSON; wird nach jeder &Auml;nderung neu gesendet.", exStations, 1);
    h += mqttRow(base, "/favorites", false, "Liste der Favoriten als JSON (bis zu 40); wird nach jeder &Auml;nderung neu gesendet. Ein Favorit l&auml;sst sich mit seiner URL auf <code>/play</code> abspielen.", exFavorites, 1);
    h += mqttRow(base, "/volume/state", false, "Gerade wirkende Lautst&auml;rke (kann die eines Senders sein).", exVolState, 1);
    h += mqttRow(base, "/volume/general", false, "Allgemeine Lautst&auml;rke.", exVolState, 1);
    h += mqttRow(base, "/availability", false, "Ger&auml;t erreichbar (<code>online</code>) oder weg (<code>offline</code>, kommt vom Broker).", exAvail, 2);
    h += "</table><p><small style='font-size:.9rem'>Fertige <code>mosquitto_pub</code>-Aufrufe zum Kopieren stehen im Tab <strong>Doku</strong>.</small></p></div>";
    return h;
}
// Text fuer ein JavaScript-Zeichenfolge in einem HTML-Attribut (confirm-Rueckfrage): \ ' " als Escape, dann HTML-sicher.
// Text for a JavaScript string inside an HTML attribute (confirm prompt): \ ' " escaped, then HTML-safe.

String jsAttrEsc(String s) {
    s.replace("\\", "\\\\");
    s.replace("'", "\\x27");
    s.replace("\"", "\\x22");
    return htmlEsc(s);
}

// Tab WLAN wie bei der Uhr: Status, Hostname, Neu scannen, Netz-Plaetze (belegte plus ein leerer), Speichern.
// WiFi tab as on the clock: status, hostname, rescan, network slots (used ones plus one empty), save.

String panelWlan() {
    String h = "<div class='card' style='text-align:center'>";
    if (apActive && WiFi.status() != WL_CONNECTED) {
        h += "<div class='flash warn'>Noch kein WLAN eingerichtet oder das zuletzt bekannte Netz ist nicht erreichbar - das Ger&auml;t hat ein eigenes WLAN aufgemacht. Zugangsdaten des Heim-WLANs unten eintragen und speichern, dann verbindet sich das Ger&auml;t.</div>";
    }
    if (WiFi.status() == WL_CONNECTED) {
        h += "<div style='margin:10px auto'>Verbunden mit: <strong>" + htmlEsc(WiFi.SSID()) + "</strong></div>";
    } else if (!apActive) {
        h += "<div style='margin:10px auto;color:#856404'>Nicht verbunden</div>";
    }
    h += "<form method='POST' action='/sethostname'><div style='display:flex;justify-content:center;align-items:center;gap:12px;flex-wrap:wrap'>";
    h += "<label>Hostname:</label> " + infoTip("Das Ger&auml;t ist auch unter http://Hostname.local erreichbar statt &uuml;ber die IP-Adresse (auch f&uuml;r OTA und die MQTT-Standardtopics). Nach einer &Auml;nderung ist ein Neustart n&ouml;tig. Nicht jeder Router l&ouml;st Hostnamen auf. Erlaubt: a-z, 0-9, Bindestrich");
    h += "<input name='host' maxlength='30' value='" + htmlEsc(cfg.host) + "' style='width:170px'>";
    h += "<button type='submit' style='width:140px'>Speichern</button></div></form><br>";
    h += "<div style='display:flex;justify-content:center;align-items:center;gap:12px;flex-wrap:wrap'>";
    h += "<button id='rescanBtn' type='button' onclick='rescanWifi()' style='width:200px'>Netzwerke neu scannen</button> " + infoTip("Sucht die WLAN-Netze in der N&auml;he erneut und f&uuml;llt die Auswahllisten unten neu") + "</div><br>";
    int saved = 0;
    for (int i = 0; i < 3; i++) {
        if (cfg.ssid[i].length() > 0) saved++;
    }
    h += "<form method='POST' action='/save'><input type='hidden' name='sect' value='wlan'>";
    for (int i = 0; i < 3; i++) {
        String n = String(i + 1);
        h += "<hr><h3 style='display:flex;align-items:center;justify-content:center;gap:6px'>SSID" + n;
        if (i == 0) h += " " + infoTip("Bis zu 3 WLAN-Netze k&ouml;nnen gespeichert werden; sie werden in dieser Reihenfolge probiert");
        h += "</h3><div style='display:flex;gap:6px;align-items:center;flex-wrap:wrap;justify-content:center'>";
        h += "<select id='ssid_select" + n + "' onchange=\"document.getElementById('ssid" + n + "').value=this.value\" style='max-width:180px'></select>";
        h += "<input name='ssid" + n + "' id='ssid" + n + "' placeholder='SSID" + n + "' value='" + htmlEsc(cfg.ssid[i]) + "' style='width:110px'>";
        h += "<input name='pass" + n + "' type='password' placeholder='Password' value='' style='width:110px'>";
        if (cfg.ssid[i].length() > 0) {
            String q = jsAttrEsc(cfg.ssid[i]);
            if (saved > 1) h += " <a href='/api/connectWifi?index=" + String(i) + "' onclick=\"return confirm('Verbinden " + q + "?')\">Verbinden</a>";
            h += " <a href='/deletewifi?index=" + String(i) + "' onclick=\"return confirm('L&ouml;schen " + q + "?')\">L&ouml;schen</a>";
        }
        h += "</div><small>Sie k&ouml;nnen auch eine SSID manuell eingeben.";
        if (cfg.ssid[i].length() > 0) h += " Das Passwort ist ausgeblendet. Lassen Sie das Feld leer, um das aktuelle Passwort beizubehalten.";
        h += "</small>";
        if (cfg.ssid[i].isEmpty()) break;
    }
    h += "<br><br><button type='submit'>WLAN Einstellungen speichern</button></form><hr></div>";
    return h;
}

String panelTime() {
    static const char* const tzValues[] = {"CET-1CEST,M3.5.0,M10.5.0/3", "CEST-2", "CET-1", "GMT0BST,M3.5.0/1,M10.5.0", "UTC0", "EST5EDT,M3.2.0,M11.1.0", "EET-2EEST,M3.5.0/3,M10.5.0/4"};
    static const char* const tzLabels[] = {"Mitteleuropa (DST auto)", "Mitteleuropa (feste Sommerzeit)", "Mitteleuropa (feste Winterzeit)", "Gro&szlig;britannien (DST auto)", "UTC", "US Ost (DST auto)", "Osteuropa (DST auto)"};
    String h = "<div class='card'><h3>Zeit</h3><form method='POST' action='/save'><input type='hidden' name='sect' value='time'>";
    int ntpVisible = 1;
    for (int i = 0; i < 5; i++) {
        if (!cfg.ntp[i].isEmpty()) ntpVisible = i + 2;
    }
    if (ntpVisible > 5) ntpVisible = 5;
    for (int i = 1; i <= 5; i++) {
        String n = String(i);
        h += "<div id='ntpRow" + n + "'" + (i > ntpVisible ? " style='display:none'" : "") + "><div class='row'>NTP Server" + n + " " + infoTip("Zeitserver (NTP), zum Beispiel pool.ntp.org") + " : <input type='text' id='ntpServerInput" + n + "' name='ntp" + n + "' value='" + htmlEsc(cfg.ntp[i - 1]) + "' oninput='ntpGrow(" + n + ")' style='width:180px'>";
        h += "<button type='button' onclick='testNtp(" + n + ")' style='width:100px'>Test</button> " + infoTip("Fragt diesen Server ab und zeigt die empfangene UTC-Zeit") + "</div><div id='ntpTestResult" + n + "'></div></div>";
    }
    h += "<small>Bis zu 5 Server, leere Felder werden &uuml;bersprungen. Das Ger&auml;t fragt die ersten drei; kommt innerhalb von 45 s keine Zeit an, probiert es die weiteren.</small>";
    h += "<div class='row'><select id='tz_select' style='width:300px' onchange=\"document.getElementById('tz_input').value=this.value\">";
    for (int i = 0; i < 7; i++) {
        h += "<option value='" + String(tzValues[i]) + "'" + (cfg.tz == tzValues[i] ? " selected" : "") + ">" + tzLabels[i] + " (" + tzValues[i] + ")</option>";
    }
    h += "</select> " + infoTip("Zeitzone aus der Liste w&auml;hlen; der Wert wird in das Feld darunter &uuml;bernommen") + "</div><div class='row'><input type='text' id='tz_input' name='tz' value='" + htmlEsc(cfg.tz) + "' style='width:300px'> " + infoTip("Zeitzone als POSIX-Text, zum Beispiel CET-1CEST,M3.5.0,M10.5.0/3") + "</div>";
    h += "<small>F&uuml;r eigene Zeitzonen eine Vorgabe w&auml;hlen oder den Wert oben selbst eintragen.</small><br>";
    h += "<button type='submit'>Speichern</button></form></div>";
    return h;
}

String statusRow(const String& label, const String& value) {
    return "<tr><td>" + label + "</td><td>" + htmlEsc(value) + "</td></tr>";
}

String panelStatus() {
    char up[32];
    unsigned long s = millis() / 1000;
    snprintf(up, sizeof(up), "%lud %02lu:%02lu:%02lu", s / 86400, (s / 3600) % 24, (s / 60) % 60, s % 60);
    String h = "<div class='card'><h3>Status</h3><table>";
    h += statusRow("Chip", String(ESP.getChipModel()));
    h += statusRow("Chip Revision", String(ESP.getChipRevision()));
    h += "<tr><td>Release</td><td><a href='https://github.com/holgiw/ESP32-netspeaker/releases/tag/v" PROJECT_VERSION "' target='_blank' rel='noopener noreferrer'>v" PROJECT_VERSION "</a></td></tr>";
    h += statusRow("Firmware", String(FIRMWARE_MARKER + FIRMWARE_MARKER_PREFIX_LEN));
    h += statusRow("Uptime", String(up));
    h += statusRow("Free Heap", String(ESP.getFreeHeap()) + " bytes (minimum since boot " + String(ESP.getMinFreeHeap()) + ")");
    h += statusRow("Reset Reason", resetReasonName());
    h += statusRow("Crashes in a Row", String(bootCrashes));
    h += statusRow("Safe Mode", safeMode ? String("ON (no MQTT, no radio reconnect)") : String("off"));
    h += statusRow("WiFi Reconnects", String(wifiReconnects));
    h += statusRow("MQTT Reconnects", String(mqttReconnects));
    h += statusRow("PSRAM", String(ESP.getPsramSize()) + " bytes (free " + String(ESP.getFreePsram()) + ")");
    h += statusRow("Flash Size", String(ESP.getFlashChipSize()) + " bytes");
    storageRefresh();
    h += statusRow("LittleFS", fsReady ? String(fsUsedC) + " / " + String(fsTotalC) + " bytes" : String("not mounted"));
    h += statusRow("SD Card", sdState);
    if (sdReady) {
        unsigned long sdTotal = (unsigned long)(sdTotalC / 1048576ULL);
        unsigned long sdUsed = (unsigned long)(sdUsedC / 1048576ULL);
        unsigned long sdFree = sdTotal > sdUsed ? sdTotal - sdUsed : 0;
        h += statusRow("SD Size", String(sdTotal) + " MB (card " + String((unsigned long)(SD.cardSize() / 1048576ULL)) + " MB)");
        h += statusRow("SD Used", String(sdUsed) + " MB" + (sdTotal > 0 ? " (" + String(sdUsed * 100UL / sdTotal) + " %)" : String()));
        h += statusRow("SD Free", String(sdFree) + " MB");
    }
    h += statusRow("SD Enabled", cfg.sdOn ? String("yes") : String("no"));
    h += statusRow("SD CS GPIO", String(cfg.sdCs));
    h += statusRow("SD SCK GPIO", String(cfg.sdSck));
    h += statusRow("SD MOSI GPIO", String(cfg.sdMosi));
    h += statusRow("SD MISO GPIO", String(cfg.sdMiso));
    h += statusRow("WiFi SSID", WiFi.status() == WL_CONNECTED ? WiFi.SSID() : String("not connected"));
    h += statusRow("WiFi RSSI", WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) + " dBm" : String("-"));
    h += statusRow("IP Address", WiFi.localIP().toString());
    h += statusRow("MAC Address", WiFi.macAddress());
    h += statusRow("Audio DIN GPIO", String(cfg.din));
    h += statusRow("Audio BCLK GPIO", String(cfg.bclk));
    h += statusRow("Audio LRC GPIO", String(cfg.lrc));
    h += statusRow("Audio State", playStateName());
    h += statusRow("Audio Last Error", lastError.length() > 0 ? lastError : String("-"));
    h += statusRow("VoiceRSS Key", cfg.vkey.length() > 0 ? String("set") : String("not set"));
    h += statusRow("MQTT Status", cfg.mqttServer.isEmpty() ? String("disabled") : (mqttClient.connected() ? String("connected") : String("disconnected")));
    h += "</table></div>";
    h += "<div class='card'><h3>Sprache / Language</h3><p>Weitere Sprachen kommen als Datei (zum Beispiel <code>en.json</code>) in den Speicher des Ger&auml;ts und werden im Browser angewendet. Mit der Schaltfl&auml;che in der Statuszeile wechselst du die Sprache.</p><div id='langList'></div>";
    h += "<div class='row'><input type='file' id='langFile' accept='.json,application/json' style='width:60%'><button type='button' onclick='langUpload()' style='width:auto;padding:8px 14px'>Hochladen</button></div>";
    h += "<div class='row'><input type='text' id='langCode' value='en.json' maxlength='24' style='width:130px'><button type='button' onclick='langFetch()' style='width:auto;padding:8px 14px'>Von GitHub laden</button> " + infoTip("L&auml;dt die Sprachdatei (zum Beispiel en.json) aus dem Ordner lang des Projekts auf GitHub (holgiw/ESP32-netspeaker) in das Ger&auml;t; dazu braucht das Ger&auml;t Internet. Eine vorhandene Datei gleichen Namens wird ersetzt") + "</div><div id='langResult'></div></div>";
    return h;
}

String panelBackup() {
    String h = "<div class='card' style='max-width:900px'><h3>Sicherung erstellen</h3>";
    h += "<p>Speichert die Einstellungen (mit Favoriten und Senderliste) als Datei auf deinem Computer. Mit Dateien im Flash entsteht eine ZIP-Datei.</p>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' id='bkWifi' style='width:auto;margin:0;'>WLAN-Zugangsdaten einschlie&szlig;en</label> " + infoTip("Nimmt die WLAN-Passw&ouml;rter in die Sicherung auf, im Klartext; die Datei gut aufbewahren. Ohne den Haken enth&auml;lt die Sicherung nur die Namen der Netze. Nur aus dem lokalen Netz m&ouml;glich") + "</div>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' id='bkFiles' style='width:auto;margin:0;'>Dateien im Flash einschlie&szlig;en</label> <small id='bkFilesInfo'></small> " + infoTip("Nimmt die MP3-Dateien aus dem Speicher des Ger&auml;ts (Tab MP3 (Flash), auch gespeicherte Texte) in eine ZIP-Datei auf. Die Dateien der SD-Karte sind nie dabei") + "</div>";
    h += "<div class='row'><button type='button' onclick='bkCreate()' style='width:auto;padding:8px 14px'>Sicherung erstellen</button></div><div id='bkResult'></div></div>";
    h += "<div class='card' style='max-width:900px'><h3>Sicherung einlesen</h3>";
    h += "<p>Liest eine Sicherung wieder ein, entweder die Textdatei mit den Einstellungen oder die ZIP-Datei mit Dateien. Bestehende Einstellungen werden &uuml;berschrieben.</p>";
    h += "<div class='row'><input type='file' id='bkFile' accept='.txt,.zip' onchange='bkPick()'></div><div id='bkInfo'></div>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' id='bkImpWifi' disabled style='width:auto;margin:0;'>WLAN-Zugangsdaten &uuml;bernehmen</label> " + infoTip("&Uuml;bernimmt die Netze und Passw&ouml;rter aus der Sicherung. Ohne den Haken bleiben die WLAN-Einstellungen des Ger&auml;ts unver&auml;ndert. Achtung: Passt das Netz nicht, ist das Ger&auml;t danach nicht mehr erreichbar. Nur aus dem lokalen Netz m&ouml;glich") + "</div>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:8px;cursor:pointer;'><input type='checkbox' id='bkImpFiles' disabled style='width:auto;margin:0;'>Dateien im Flash &uuml;bernehmen</label> " + infoTip("Spielt die MP3-Dateien aus der ZIP-Datei in den Speicher des Ger&auml;ts ein; Dateien gleichen Namens werden ersetzt") + "</div>";
    h += "<div class='row'><button type='button' id='bkRestoreBtn' onclick='bkRestore()' disabled style='width:auto;padding:8px 14px'>Einlesen</button></div><div id='bkRestoreResult'></div></div>";
    return h;
}

String panelLog() {
    String h = "<div class='card' style='max-width:900px'><form method='POST' action='/save'><input type='hidden' name='sect' value='log'>";
    h += "<div class='row'><label style='display:flex;align-items:center;gap:6px;cursor:pointer;'><input type='checkbox' name='log' value='1'" + String(cfg.logEnabled ? " checked" : "") + " style='width:auto;margin:0;'>Log in Datei schreiben (Standard: aus)</label> " + infoTip("Schreibt Ereignisse in eine Datei im Flash (nur zur Fehlersuche; Standard: aus)") + " automatisch aus nach <input type='number' name='logmin' min='0' max='1440' value='" + String(cfg.logAutoMin) + "' style='width:70px'> min " + infoTip("Schaltet das Schreiben des Logs in die Datei nach so vielen Minuten von selbst aus, damit der Flash geschont wird; 0 = nie. Die Zeit l&auml;uft ab dem Einschalten oder ab dem Start des Ger&auml;ts") + "";
    h += "<button type='submit' style='width:auto;padding:8px 16px;margin:6px;'>Speichern</button>";
    h += "<button type='button' onclick='clearLog()' style='width:auto;padding:8px 16px;margin:6px;background:var(--panel);border:1px solid var(--panel-border);color:var(--text);font-weight:normal;'>Log leeren</button></div>";
    h += "<small>Ausgeschaltet wird nichts in den Flash geschrieben; die serielle Ausgabe l&auml;uft immer.</small><div id='logResult'></div></form></div>";
    h += "<div class='card' style='max-width:900px'>";

    // Karte so breit wie das Log-Feld darunter (max-width:900px); beide Werte gehoeren zusammen.
    // Card as wide as the log box below (max-width:900px); both values belong together.

    h += "<div style='display:flex;align-items:center;gap:14px;flex-wrap:wrap;'>";
    h += "<label style='display:flex;align-items:center;gap:6px;white-space:nowrap;cursor:pointer;'><input type='checkbox' id='logAutoRefresh' style='width:auto;margin:0;'>Auto-Aktualisierung (10 s)</label> " + infoTip("Holt das Log alle 10 Sekunden neu") + "";
    h += "<button type='button' id='logRefreshNow' style='background:var(--panel);border:1px solid var(--panel-border);color:var(--text);border-radius:.4rem;padding:4px 12px;font-size:.8rem;cursor:pointer;width:auto;margin:0;font-weight:normal;'>Jetzt aktualisieren</button>";
    h += "<span id='logErrorHint' class='offline-hint'>&#9888; Aktualisierung fehlgeschlagen - letzter Stand wird angezeigt</span></div>";
    h += "<pre id='logContent' style='background:var(--panel);border:1px solid var(--panel-border);border-radius:10px;max-width:900px;height:400px;overflow-y:auto;margin:15px auto;padding:12px 16px;text-align:left;white-space:pre-wrap;word-break:break-word;font-family:monospace;font-size:.85rem;'>Lade &hellip;</pre></div>";
    return h;
}

// Doku-Tab: Aufrufe von REST-API und MQTT; @HOST@ ersetzt das Skript durch die Adresse, unter der die Seite gerade geoeffnet ist.
// Docs tab: calls of the REST API and MQTT; the script replaces @HOST@ with the address the page is currently opened under.

String docCode(const String& code, bool withHost = true) {
    return "<div class='codewrap'><button type='button' class='copy-btn' onclick='copyPre(this)'>Kopieren</button><pre class='code" + String(withHost ? " codehost" : "") + "'>" + htmlEsc(code) + "</pre></div>";
}

String docCard(const String& title, const String& text, const String& code, bool withHost = true) {
    String h = "<div class='card doc' style='max-width:900px'><h3>" + title + "</h3>";
    if (text.length() > 0) h += "<p>" + text + "</p>";
    if (code.length() > 0) h += docCode(code, withHost);
    return h + "</div>";
}

String panelDoc() {
    String base = mqttBaseTopic();
    String h = docCard("Allgemein",
        "Alle Aufrufe gehen an <code>http://" + htmlEsc(cfg.host) + ".local/</code> oder an die IP-Adresse. Parameter k&ouml;nnen als Formular (<code>-d</code>), als Query (<code>?text=...</code>) oder als flaches JSON im Body kommen; Aufrufe per GET sind erlaubt, zum Beispiel f&uuml;r Home-Automation. "
        "Antwort: <code>{\"ok\":true,\"msg\":\"...\"}</code> oder bei einem Fehler HTTP 400 mit <code>{\"ok\":false,\"error\":\"...\"}</code>. Texte kommen in eine Warteschlange (bis zu 8) und laufen nacheinander. Eine MP3-Datei startet sofort, auch wenn schon eine andere l&auml;uft: bis zu zwei Dateien spielen &uuml;bereinander (zum Beispiel Vogelgezwitscher mit einer Glocke dar&uuml;ber), eine dritte wartet. Ein Sender-Befehl wirkt sofort, ein Stopp leert die Warteschlange.", "");
    {
        // Verkabelungsbild: die GPIO-Nummern im Bild sind die eingestellten Pins.
        // Wiring picture: the GPIO numbers in the picture are the configured pins.

        String svg = FPSTR(WIRING_SVG);
        svg.replace("GPIO 3 (BCLK)", "GPIO " + String(cfg.bclk) + " (BCLK)");
        svg.replace("GPIO 4 (LRC)", "GPIO " + String(cfg.lrc) + " (LRC)");
        svg.replace("GPIO 2 (DIN)", "GPIO " + String(cfg.din) + " (DIN)");
        svg.replace("GPIO 10 (MISO)", "GPIO " + String(cfg.sdMiso) + " (MISO)");
        svg.replace("GPIO 11 (CLK)", "GPIO " + String(cfg.sdSck) + " (CLK)");
        svg.replace("GPIO 12 (MOSI)", "GPIO " + String(cfg.sdMosi) + " (MOSI)");
        svg.replace("GPIO 13 (CS)", "GPIO " + String(cfg.sdCs) + " (CS)");
        h += "<div class='card doc' style='max-width:900px'><h3>Verkabelung</h3><p>Anschl&uuml;sse von ESP32-S3, MAX98357A-Verst&auml;rker und SD-Kartenleser (optional). Die GPIO-Nummern im Bild sind die im Tab Audio eingestellten Pins.</p>";
        h += "<div style='background:#fff;border-radius:8px;padding:6px;overflow-x:auto'>" + svg + "</div></div>";

        // Hier wird die Ansicht (WIRING_VIEW_SVG) eingefuegt; sie wird direkt aus dem Flash gesendet, nicht in einen String kopiert.
        // The view (WIRING_VIEW_SVG) is inserted here; it is sent straight from flash, not copied into a string.

        h += "<!--WIRING_VIEW-->";
    }
    h += docCard("Text ansagen (VoiceRSS)",
        "<code>text</code> (Pflicht, h&ouml;chstens 500 Zeichen), optional <code>save</code> (1 = Text dauerhaft speichern, bevorzugt auf der SD-Karte, sonst im Flash), <code>fx</code> (0 = ohne Klangeffekt, Standard 1), <code>lang</code> (z. B. de-de, en-gb), <code>voice</code> (z. B. Hanna), <code>rate</code> (-10 bis 10), <code>vol</code> (0-100). Ohne Angabe gelten die Werte aus dem Tab VoiceRSS. Der API-Schl&uuml;ssel muss gespeichert sein.",
        R"d(curl -d "text=Hallo Welt" http://@HOST@/api/say
curl "http://@HOST@/api/say?text=Hallo%20Welt&lang=en-gb&voice=Alice&vol=10"
curl -H "Content-Type: application/json" -d '{"text":"Hallo Welt","lang":"de-de","voice":"Hanna","rate":0,"vol":12}' http://@HOST@/api/say)d");
    h += docCard("Webradio oder MP3 per URL",
        "<code>url</code> muss mit http:// oder https:// beginnen. <code>/api/play</code> nimmt <code>url</code> oder <code>file</code>, <code>/api/url</code> nur eine URL. Optional <code>vol</code>. Webradio &uuml;ber https braucht viel RAM, http-Streams sind unkritisch. L&auml;uft ein Webradio und kommt eine Ansage oder eine MP3-Datei, wird das Radio daf&uuml;r ausgeblendet und gestoppt (also stumm), die Ansage gespielt und das Radio danach mit der alten Lautst&auml;rke neu verbunden; vorher wird es sanft ausgeblendet und beim Fortsetzen wieder eingeblendet (Dauer im Tab Audio, Standard 700 ms). Ein Webradio wird beim Start (aus dem Leerlauf) langsam eingeblendet, beim Stopp langsam ausgeblendet, und bei einem Senderwechsel wird der alte langsam aus- und der neue langsam eingeblendet (Tab Audio, Standard 1500 ms). Wird derselbe Sender noch einmal gew&auml;hlt, spielt er einfach weiter; ein Live-Stream geht live weiter, nicht an derselben Stelle. <code>/api/stop</code> beendet das Radio ohne Fortsetzung, ein neuer URL-Befehl ersetzt es.",
        R"d(curl -d "url=http://stream.example.com/radio.mp3" http://@HOST@/api/play
curl -d "url=http://stream.example.com/radio.mp3" http://@HOST@/api/url
curl "http://@HOST@/api/url?url=http://stream.example.com/radio.mp3&vol=10")d");
    h += docCard("SD-Karte",
        "Dateien der SD-Karte (FAT32, nur MP3) werden mit dem Namen <code>sd:/Ordner/Datei.mp3</code> angesprochen, in <code>file</code> von <code>/api/play</code> und <code>/api/file</code> und ebenso per MQTT (<code>/file</code>, <code>/play</code>). Endet der Name mit <code>/</code>, spielt das Ger&auml;t alle MP3-Dateien des Ordners nacheinander (nach Name sortiert); sie kommen einzeln in die Warteschlange, Ansagen dazwischen kommen zuerst. Mit <code>shuffle=1</code> ist die Reihenfolge je Sitzung zuf&auml;llig und jede Datei kommt einmal vor, die erste ist nie die der letzten Sitzung dieses Ordners; mit <code>loop=1</code> beginnt nach der letzten Datei eine neue Runde (bei shuffle neu gemischt, die erste Datei ist nie die zuletzt gespielte). Ein neuer Sender oder Stopp beendet die Sitzung. <code>/api/sd?dir=/Ordner</code> listet einen Ordner, <code>/api/sdmount</code> bindet die Karte neu ein. Dateimanager: Hochladen mit <code>/upload?target=sd&amp;dir=/Ordner</code>, <code>/api/sdmkdir</code> (dir, name), <code>/api/sdrename</code> (path, to), <code>/api/sddelete</code> (path; ein Ordner wird samt Inhalt gel&ouml;scht) und <code>/api/sdfile?path=...</code> zum Herunterladen. Namen werden bereinigt (Umlaute umgeschrieben, Leerzeichen zu Unterstrichen). Ansagen k&ouml;nnen auf der Karte zwischengespeichert werden (Tab Audio, Sprachausgabe): <code>GET /api/ttscache</code> liefert <code>enabled</code>, <code>files</code> und <code>bytes</code>, <code>POST /api/ttscache</code> mit <code>clear=1</code> l&ouml;scht den Zwischenspeicher (Ordner <code>/tts</code>, Dateinamen wie <code>Achtung_auf_Gleis_3_3fa9c2e1.mp3</code>, h&ouml;chstens 500).",
        R"d(curl -d "file=sd:/Musik/lied.mp3" http://@HOST@/api/play
curl -d "file=sd:/Musik/Album/" http://@HOST@/api/play
curl -d "file=sd:/Musik/&shuffle=1&loop=1" http://@HOST@/api/play
curl "http://@HOST@/api/file?file=sd:/Musik/lied.mp3&pan=lr&pansec=5"
curl "http://@HOST@/api/sd?dir=/Musik"
curl -F "file=@lied.mp3" "http://@HOST@/upload?target=sd&dir=/Musik"
curl -d "dir=/Musik&name=Neu" http://@HOST@/api/sdmkdir
curl -d "path=/Musik/lied.mp3&to=neu.mp3" http://@HOST@/api/sdrename
curl -d "path=/Musik/lied.mp3" http://@HOST@/api/sddelete
curl -o lied.mp3 "http://@HOST@/api/sdfile?path=/Musik/lied.mp3"
curl -X POST http://@HOST@/api/sdmount
curl http://@HOST@/api/ttscache
curl -d "clear=1" http://@HOST@/api/ttscache)d");
    h += docCard("Gespeicherte Webradios / URLs",
        "Im Tab Webradio lassen sich 30 Pl&auml;tze mit Name, URL und eigener Lautst&auml;rke speichern (leer = allgemeine Lautst&auml;rke; ein <code>vol</code> im Aufruf hat Vorrang). <code>n</code> ist die Platznummer (1-30), alternativ <code>name</code> (Gro&szlig;-/Kleinschreibung egal). <code>/api/stations</code> liefert die belegten Pl&auml;tze (JSON mit n, name, url, vol), <code>/api/stationdelete</code> l&ouml;scht einen Platz (Name und URL), die folgenden Pl&auml;tze r&uuml;cken nach oben. <code>/stations.txt</code> l&auml;dt die Liste als Textdatei, <code>POST /importstations</code> ersetzt sie durch eine solche Datei (im Tab Webradio: Liste speichern / Liste laden). <code>POST /api/stationlist</code> mit <code>list=aac-auswahl</code> l&auml;dt eine fertige Liste von GitHub.",
        R"d(curl -d "n=3" http://@HOST@/api/station
curl "http://@HOST@/api/station?name=Radio%20Eins&vol=10"
curl http://@HOST@/api/stations
curl http://@HOST@/stations.txt -o stations.txt
curl --data-binary @stations.txt -H "Content-Type: text/plain" http://@HOST@/importstations
curl -d "n=3" http://@HOST@/api/stationdelete)d");
    h += docCard("Hochgeladene MP3-Datei abspielen",
        "<code>file</code> ist der Dateiname aus dem Tab MP3 (Flash). Dort gibt es f&uuml;r jede Datei Kn&ouml;pfe, die den fertigen Aufruf kopieren. Mit <code>/api/files</code> kommt die Liste, mit <code>/api/delete</code> wird eine Datei gel&ouml;scht. Hochladen geht per <code>/upload</code> (Formular, Feld <code>file</code>). <code>/api/flash?dir=</code> zeigt einen Ordner wie bei der SD-Karte (leer = MP3-Ordner, <code>ansagen</code> = gespeicherte Texte), <code>/api/fileget?file=</code> l&auml;dt eine Datei herunter. Ein Name wie <code>ansagen/Text.mp3</code> liegt im Unterordner; endet der Name mit <code>/</code> (<code>ansagen/</code> oder <code>/</code> f&uuml;r den MP3-Ordner), spielt das Ger&auml;t alle Dateien des Ordners (mit <code>shuffle=1</code> zuf&auml;llig). Ein Name ohne <code>sd:</code> wird zuerst im Flash und dann auf der SD-Karte gesucht (<code>sd:/Pfad.mp3</code> nur auf der Karte).",
        R"d(curl -d "file=glocke.mp3" http://@HOST@/api/file
curl "http://@HOST@/api/file?file=glocke.mp3&vol=15"
curl http://@HOST@/api/files
curl -d "file=glocke.mp3" http://@HOST@/api/delete
curl -d "file=glocke.mp3&to=gong.mp3" http://@HOST@/api/rename
curl -F "file=@glocke.mp3" http://@HOST@/upload)d");
    h += docCard("Stopp, Lautst&auml;rke, Status",
        "<code>v</code> ist 0-100 und wird gespeichert; die Lautst&auml;rke wandert sanft zum neuen Wert, die Dauer in Millisekunden steht im Tab Audio und l&auml;sst sich je Aufruf mit <code>ms</code> &uuml;berschreiben. Ohne <code>v</code> meldet <code>/api/volume</code> nur: <code>volume</code> (allgemein) und <code>playVolume</code> (gerade wirkend). <code>/api/status</code> liefert <code>state</code> (idle, loading, playing), <code>error</code>, <code>queue</code> (wartende Ansagen und Dateien), <code>volume</code> (allgemein), <code>playVolume</code> (die gerade wirkende Lautst&auml;rke), den freien Speicher und was gerade l&auml;uft: <code>source</code> (radio, file, speech), <code>name</code> (Sendername oder Dateiname), <code>title</code> (aktueller Titel, wenn der Sender ihn meldet) und <code>url</code>. Bei einer laufenden Datei kommen <code>pos</code> und <code>dur</code> (Sekunden), <code>pm</code> (Fortschritt in Promille) und <code>rate</code> (Promille je Sekunde) dazu, bei einem Webradio <code>genre</code>, <code>desc</code>, <code>web</code>, <code>logo</code>, <code>host</code>, <code>bitrate</code>, <code>codec</code>, <code>rate</code> (Abtastrate in Hz), <code>ch</code> und <code>bits</code>, und mit der Lautst&auml;rke-Angleichung <code>gainDb</code>.",
        R"d(curl -X POST http://@HOST@/api/stop
curl -d "toggle=1" http://@HOST@/api/mute
curl -d "on=1" http://@HOST@/api/mute
curl -d "on=0" http://@HOST@/api/mute
curl http://@HOST@/api/mute
curl -d "v=50" http://@HOST@/api/volume
curl -d "v=60&ms=3000" http://@HOST@/api/volume
curl http://@HOST@/api/volume
curl http://@HOST@/api/status)d");
    h += docCard("Log",
        "<code>enable</code> schaltet das Log in die Datei ein (1) oder aus (0), Standard ist aus. <code>clear=1</code> leert die Datei. Ohne Parameter liefert GET den Zustand. <code>/log</code> gibt den Inhalt als Text zur&uuml;ck.",
        R"d(curl http://@HOST@/api/log
curl -d "enable=1" http://@HOST@/api/log
curl -d "clear=1" http://@HOST@/api/log
curl http://@HOST@/log)d");
    h += docCard("MQTT-Broker per API setzen",
        "Setzt nur Broker und Port (optional auch <code>user</code> und <code>pass</code>), alles andere bleibt unver&auml;ndert. GET liefert Broker, Port, <code>user</code> und <code>connected</code>; das Passwort wird nie ausgegeben. Mit <code>group1</code> bis <code>group5</code> lassen sich die Gruppen-Topics setzen (leer = entfernt); GET liefert sie als <code>groups</code>. <code>ha=1</code> schaltet die Home-Assistant-Discovery ein, <code>ha=0</code> aus.",
        R"d(curl -d "broker=192.168.0.70&port=1883" http://@HOST@/api/mqtt
curl -d "group1=netspeaker/all&group2=netspeaker/haus" http://@HOST@/api/mqtt
curl -d "ha=1" http://@HOST@/api/mqtt
curl http://@HOST@/api/mqtt)d");
    h += docCard("Eing&auml;nge (Pins)",
        "<code>GET /api/pins</code> liefert die freien Pins: <code>p</code> (Nummer), <code>l</code> (Zustand, 1 = High, 0 = Low), <code>t</code> (Aktion), <code>x</code> (Text) und <code>v</code> (Lautst&auml;rke, -1 = allgemeine). <code>POST /api/pins</code> mit <code>pin</code>, <code>type</code> (<code>say</code>, <code>file</code>, <code>station</code>, <code>radio</code>, <code>next</code>, <code>prev</code>, <code>volup</code>, <code>voldown</code>, <code>mute</code>, <code>stop</code> oder leer = keine Aktion; die letzten sieben brauchen keinen Text, bei <code>volup</code>/<code>voldown</code> gilt <code>vol</code> als Schrittweite, Standard 5), <code>text</code> (Ansage, Dateiname, <code>sd:</code>-Pfad, URL oder Sender) und optional <code>vol</code> (0-100) speichert die Aktion eines Pins. Sie l&ouml;st aus, sobald der Pin etwa 40 ms Kontakt nach GND hat.",
        R"d(curl http://@HOST@/api/pins
curl -d "pin=5&type=say&text=Die Tür ist offen" http://@HOST@/api/pins
curl -d "pin=6&type=file&text=gong.mp3&vol=60" http://@HOST@/api/pins
curl -d "pin=7&type=station&text=RSA" http://@HOST@/api/pins
curl -d "pin=5&type=" http://@HOST@/api/pins)d");
    h += docCard("Sprachen",
        "Sprachdateien (zum Beispiel <code>en.json</code>) liegen im Speicher des Ger&auml;ts. <code>/upload?target=lang</code> (Formular, Feld <code>file</code>) l&auml;dt eine hoch, <code>GET /api/lang</code> listet die vorhandenen Sprachen, <code>POST /api/lang</code> mit <code>fetch=en</code> l&auml;dt die Datei vom Projekt auf GitHub, mit <code>delete=en</code> l&ouml;scht sie, und <code>/lang.json?l=en</code> liefert die Datei.",
        R"d(curl http://@HOST@/api/lang
curl -F "file=@en.json" "http://@HOST@/upload?target=lang"
curl -d "fetch=en" http://@HOST@/api/lang
curl -d "delete=en" http://@HOST@/api/lang
curl "http://@HOST@/lang.json?l=en")d");
    h += docCard("Klangeffekte",
        "<code>GET /api/effect</code> liefert <code>mode</code> (off, room, hall, church, echo), <code>wet</code> (0-100), <code>bass</code>, <code>treble</code> (dB), <code>pan</code> (off, lr = links&rarr;rechts, rl = rechts&rarr;links, pp = hin und her), <code>pansec</code> (Dauer eines Durchgangs, 0,5-20 s) und <code>load</code> (Rechenlast des Effekts in Prozent). <code>POST /api/effect</code> setzt die angegebenen Werte; <code>mode</code> auch als Zahl 0-4 oder auf Deutsch (aus, zimmer, halle, kirche, echo), <code>bass</code> und <code>treble</code> -12 bis 12 dB. Hall und Echo wirken nur auf Ansagen, Klangregler und Wandern auch auf abgespielte Dateien, nie auf Webradio. Die Werte bleiben gespeichert; im Tab Ansage einstellbar. Mit <code>fx=0</code> bei <code>/api/say</code> l&auml;uft eine einzelne Ansage ohne Effekt.",
        R"d(curl http://@HOST@/api/effect
curl -d "mode=hall&wet=35" http://@HOST@/api/effect
curl -d "bass=4&treble=-2" http://@HOST@/api/effect
curl -d "mode=off" http://@HOST@/api/effect)d");
    h += docCard("Sicherung",
        "Im Tab Sicherung entsteht die Sicherung im Browser: <code>GET /export</code> liefert die Einstellungen als Textdatei, mit <code>wifi=1</code> auch die WLAN-Passw&ouml;rter (nur aus dem lokalen Netz). <code>GET /api/files</code> listet die MP3-Dateien im Flash, <code>GET /api/fileget?file=name.mp3</code> l&auml;dt eine herunter. Mit Dateien packt der Browser alles in eine ZIP-Datei (<code>settings.txt</code> und <code>mp3/&lt;Name&gt;</code>). Zum Einlesen sendet er <code>POST /import</code> (Text) und <code>POST /upload</code> je Datei. Die Dateien der SD-Karte sind nie Teil der Sicherung.",
        R"d(curl -o netspeaker-settings.txt "http://@HOST@/export?wifi=1"
curl -o glocke.mp3 "http://@HOST@/api/fileget?file=glocke.mp3"
curl --data-binary @netspeaker-settings.txt -H "Content-Type: text/plain" http://@HOST@/import)d");
    h += docCard("Weitere Aufrufe",
        "<code>/api/scan</code> (WLAN-Suche), <code>/api/scanwifi</code> (Suche im Hintergrund mit Signalst&auml;rke, Ergebnis aus dem Zwischenspeicher) und <code>/api/rescanwifi</code> (POST, neu suchen),<code>/api/testNtp?server=...</code> (NTP-Test, nur im Tab Zeit n&ouml;tig), <code>/api/topbarStatus</code> (Statusleiste), <code>/api/version</code> (Firmware-Stand), <code>/export</code> und <code>/import</code> (Einstellungen; WLAN-Passw&ouml;rter nur mit <code>/export?wifi=1</code>, API-Schl&uuml;ssel und MQTT-Passwort nie, siehe Karte Sicherung), <code>/restart</code> (POST, Neustart).",
        R"d(curl http://@HOST@/api/version
curl -o netspeaker-settings.txt http://@HOST@/export
curl -X POST http://@HOST@/restart)d");
    h += docCard("MQTT",
        "Basis-Topic <code>" + htmlEsc(base) + "</code> (im Tab MQTT &auml;nderbar). Nutzlast als Text oder als JSON. <code>/say</code>: Text oder <code>{\"text\":\"...\",\"lang\":\"..\",\"voice\":\"..\",\"rate\":0,\"vol\":60,\"fx\":0}</code>. <code>/play</code>: URL oder Dateiname, auch <code>{\"url\":\"...\"}</code> oder <code>{\"file\":\"...\"}</code>. <code>/url</code> nur URL, <code>/file</code> nur Dateiname, <code>/station</code> Platz 1-30 oder Name (auch JSON <code>{\"n\":3}</code> oder <code>{\"name\":\"..\"}</code>). <code>/stop</code> ohne Nutzlast. <code>/volume</code> 0-100. <code>/restart</code> ohne Nutzlast startet das Ger&auml;t neu (nicht retained senden; eine Nachricht in den ersten 3 s nach dem Verbinden wird ignoriert). "
        "Zur&uuml;ck kommen <code>/status</code> (idle, loading, playing, error: ...), <code>/now</code> (was gerade l&auml;uft, zum Beispiel &quot;Sendername - Titel&quot;) und <code>/availability</code> (online, offline). <code>/volume/state</code> (gerade wirkende Lautst&auml;rke) und <code>/volume/general</code> (allgemeine) werden bei jeder &Auml;nderung gesendet. <code>/stations</code> enth&auml;lt die Senderliste (retained, wird nach jeder &Auml;nderung neu gesendet); ein Aufruf von <code>/list</code> sendet sie erneut; ein ung&uuml;ltiger Befehl erscheint in <code>/status</code> als Fehler. Zus&auml;tzliche Gruppen-Topics (bis zu 5, im Tab MQTT) nehmen dieselben Befehle an, zum Beispiel <code>netspeaker/all/stop</code> f&uuml;r alle Ger&auml;te; Standard ist <code>netspeaker/all</code>.",
        "mosquitto_pub -h <broker> -t " + base + "/say -m \"Hallo Welt\"\n"
        "mosquitto_pub -h <broker> -t " + base + "/say -m '{\"text\":\"Hallo\",\"lang\":\"en-gb\",\"vol\":10}'\n"
        "mosquitto_pub -h <broker> -t " + base + "/play -m \"http://stream.example.com/radio.mp3\"\n"
        "mosquitto_pub -h <broker> -t " + base + "/file -m \"glocke.mp3\"\n"
        "mosquitto_pub -h <broker> -t " + base + "/station -m 3\n"
        "mosquitto_pub -h <broker> -t " + base + "/station -m \"Radio Eins\"\n"
        "mosquitto_pub -h <broker> -t " + base + "/stop -n\n"
        "mosquitto_pub -h <broker> -t " + base + "/volume -m 50\n"
        "mosquitto_pub -h <broker> -t " + base + "/list -n\n"
        "mosquitto_pub -h <broker> -t " + base + "/restart -n\n"
        "mosquitto_sub -h <broker> -t " + base + "/stations -C 1\n"
        "mosquitto_sub -h <broker> -t \"" + base + "/#\" -v", false);
    h += docCard("Kontakt", "E-Mail: <a href='mailto:carleaner@gmx.de'>carleaner@gmx.de</a><br>GitHub: <a href='https://github.com/holgiw/ESP32-netspeaker' target='_blank' rel='noopener'>github.com/holgiw/ESP32-netspeaker</a>", "");
    return h;
}
static const char PINS_JS[] PROGMEM = R"js(
(function(){
  var picks=[],spicks=[],fl=[],sdl=[],stl=[],rows=[];
  function el(n,c){var e=document.createElement(n);if(c)e.className=c;return e;}
  function fillPick(p){
    p.textContent='';var o=el('option');o.value='';o.textContent='Datei w\u00e4hlen \u2026';p.appendChild(o);
    if(fl.length){var g=el('optgroup');g.label='Flash';fl.forEach(function(f){var x=el('option');x.value=f;x.textContent=f;g.appendChild(x);});p.appendChild(g);}
    if(sdl.length){var g2=el('optgroup');g2.label='SD-Karte';sdl.forEach(function(s){var x=el('option');x.value=s[0];x.textContent=s[1];g2.appendChild(x);});p.appendChild(g2);}
  }
  function fillSta(p){p.textContent='';var o=el('option');o.value='';o.textContent='Sender w\u00e4hlen \u2026';p.appendChild(o);stl.forEach(function(s){var x=el('option');x.value=s[0];x.textContent=s[1];p.appendChild(x);});}
  function lists(cb){
    Promise.all([
      fetch('/api/files',{cache:'no-store'}).then(function(r){return r.json();}).catch(function(){return {};}),
      fetch('/api/sd?dir=/',{cache:'no-store'}).then(function(r){return r.json();}).catch(function(){return {};}),
      fetch('/api/stations',{cache:'no-store'}).then(function(r){return r.json();}).catch(function(){return {};})
    ]).then(function(a){
      stl=((a[2]&&a[2].stations)||[]).map(function(s){return [s.name||String(s.n),s.n+': '+(s.name||s.url)];});
      fl=(a[0].files||[]).map(function(f){return f.name;});
      sdl=[];var s=a[1];
      if(s&&s.mounted){sdl.push(['sd:/','\uD83D\uDCC1 / (Hauptverzeichnis)']);(s.entries||[]).forEach(function(e){sdl.push(e.d?['sd:/'+e.n+'/','\uD83D\uDCC1 '+e.n]:['sd:/'+e.n,e.n]);});}
      picks.forEach(fillPick);spicks.forEach(fillSta);if(cb)cb();
    });
  }
  var LV={};
  function build(list){
    var tb=document.getElementById('pinTable');if(!tb)return;tb.textContent='';picks=[];spicks=[];rows=[];LV={};
    list.forEach(function(j){LV[j.p]=j.l;});
    var h=el('tr');['GPIO','Zustand','Aktion','Text oder Datei','Lautst\u00e4rke'].forEach(function(t){var c=el('th');c.textContent=t;h.appendChild(c);});tb.appendChild(h);
    function addRow(j,free){
      var tr=el('tr'),c1=el('td'),c2=el('td'),c3=el('td'),c4=el('td'),c5=el('td'),gp=null;
      if(free){gp=el('select');gp.style.cssText='width:auto;margin:2px';free.forEach(function(q){var o=el('option');o.value=q.p;o.textContent='GPIO '+q.p;gp.appendChild(o);});c1.appendChild(gp);}
      else c1.textContent='GPIO '+j.p;
      c1.style.whiteSpace='nowrap';c2.style.whiteSpace='nowrap';
      var st=el('span');c2.appendChild(st);
      var sel=el('select');sel.style.cssText='width:auto;margin:2px';[['','Keine Aktion'],['say','Ansage (VoiceRSS)'],['file','MP3-Datei / URL'],['station','Webradio'],['radio','Radio starten'],['next','Sender vor'],['prev','Sender zur\u00fcck'],['volup','Lauter'],['voldown','Leiser'],['mute','Stumm (umschalten)'],['stop','Stopp']].forEach(function(o){var op=el('option');op.value=o[0];op.textContent=o[1];sel.appendChild(op);});sel.value=j.t||'';c3.appendChild(sel);
      var tx=el('input');tx.type='text';tx.maxLength=300;tx.value=j.x||'';tx.placeholder='z. B. Die T\u00fcr ist offen / gong.mp3';tx.style.cssText='width:95%;margin:2px';c4.appendChild(tx);
      var pk=el('select');pk.style.cssText='width:95%;margin:2px';fillPick(pk);picks.push(pk);c4.appendChild(pk);
      pk.onchange=function(){if(pk.value){tx.value=pk.value;pk.value='';}};
      var ps=el('select');ps.style.cssText='width:95%;margin:2px';fillSta(ps);spicks.push(ps);c4.appendChild(ps);
      ps.onchange=function(){if(ps.value){tx.value=ps.value;ps.value='';}};
      function vis(){var v=sel.value,ctl=['radio','next','prev','mute','stop','volup','voldown'].indexOf(v)>=0,stp=v==='volup'||v==='voldown';pk.style.display=v==='file'?'':'none';ps.style.display=v==='station'?'':'none';tx.style.display=(ctl||v==='')?'none':'';if(vo){vo.style.display=(v===''||v==='mute'||v==='stop')?'none':'';vo.placeholder=stp?'Schritt 5':'Std';if(stp){if(vo.value===''){vo.value='5';vo.dataset.auto='1';}}else if(vo.dataset.auto==='1'){if(vo.value==='5')vo.value='';vo.dataset.auto='';}}if(tip)tip.style.display=stp?'':'none';}
      sel.onchange=vis;
      var vo=el('input');vo.type='number';vo.min=0;vo.max=100;vo.value=j.v>=0?j.v:'';vo.style.cssText='width:64px;margin:2px';c5.appendChild(vo);
      var tip=el('span');tip.textContent='\u24d8';tip.style.cssText='cursor:help;margin-left:4px';tip.title='Schrittweite: Um wie viele Lautst\u00e4rke-Stufen (0-100) sich die Lautst\u00e4rke mit jedem Tastendruck \u00e4ndert. Standard 5.';c5.appendChild(tip);
      vis();
      var row={sel:sel,tx:tx,vo:vo};
      row.pin=function(){return gp?gp.value:String(j.p);};
      row.cur=function(){return JSON.stringify([sel.value,tx.value,vo.value]);};
      row.orig=row.cur();
      row.dirty=function(){return gp?sel.value!=='':row.cur()!==row.orig;};
      row.upd=function(){var l=LV[row.pin()];st.textContent=l?'High':'Low (GND)';st.style.color=l?'var(--muted)':'var(--ok)';st.style.fontWeight=l?'normal':'bold';};
      if(gp)gp.onchange=row.upd;
      rows.push(row);row.upd();
      [c1,c2,c3,c4,c5].forEach(function(c){tr.appendChild(c);});tb.appendChild(tr);
    }
    var used=list.filter(function(j){return j.t;}),free=list.filter(function(j){return !j.t;});
    used.forEach(function(j){addRow(j,null);});
    if(free.length)addRow({t:'',x:'',v:-1},free);
    else if(!used.length){var r=el('tr'),c=el('td');c.textContent='Keine freien Pins';r.appendChild(c);tb.appendChild(r);}
  }
  function saveAll(){
    var todo=rows.filter(function(r){return r.dirty();}),n=0,bad='';
    if(!todo.length){showRes('pinResult',{ok:true,msg:'Keine \u00c4nderungen'});return;}
    todo.reduce(function(pr,r){return pr.then(function(){return fetch('/api/pins',{method:'POST',body:new URLSearchParams({pin:r.pin(),type:r.sel.value,text:r.tx.value,vol:r.vo.value})}).then(function(x){return x.json();}).then(function(j){if(j.ok)n++;else bad=bad||(j.error||'Fehler');}).catch(function(){bad=bad||'Keine Antwort vom Ger\u00e4t';});});},Promise.resolve())
    .then(function(){showRes('pinResult',bad?{ok:false,error:bad}:{ok:true,msg:n+(n===1?' Pin gespeichert':' Pins gespeichert')});if(n>0)load(true);});
  }
  function load(first){fetch('/api/pins',{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){var l=j.pins||[];if(first)build(l);else{l.forEach(function(q){LV[q.p]=q.l;});rows.forEach(function(r){r.upd();});}}).catch(function(){});}
  var ready=false;
  window.pinsInit=function(){var sv=document.getElementById('pinSave');if(sv)sv.onclick=saveAll;ready=true;lists(function(){load(true);});};
  var tab=document.getElementById('tab-pins');if(tab)tab.addEventListener('change',function(){if(tab.checked&&ready)lists();});
  setInterval(function(){var t=document.getElementById('tab-pins');if(document.hidden||!t||!t.checked)return;load(false);},1000);
})();
)js";
static const char LANG_JS[] PROGMEM = R"js(
(function(){
  var code='';try{code=localStorage.getItem('uilang')||'';}catch(e){}
  var T=null,R=[],mo=null,SKIP=/^(SCRIPT|STYLE|CODE|PRE|TEXTAREA|SVG)$/,INL=/^(CODE|EM|STRONG|B|KBD)$/,ATTR=['title','placeholder','aria-label','label'];
  function norm(s){return s.replace(/\s+/g,' ').trim();}
  function look(k){var kk=UI_HOST?k.split(UI_HOST).join('{host}'):k,v=T[kk];
    if(v===undefined){for(var i=0;i<R.length;i++){if(R[i][0].test(kk)){v=kk.replace(R[i][0],R[i][1]);break;}}}
    return v===undefined?undefined:(UI_HOST?v.split('{host}').join(UI_HOST):v);}
  function trText(s){var k=norm(s);if(!k)return s;var v=look(k);if(v===undefined)return s;return s.match(/^\s*/)[0]+v+s.match(/\s*$/)[0];}
  function safe(v){var tp=document.createElement('template');tp.innerHTML=v;[].forEach.call(tp.content.querySelectorAll('*'),function(e){if(!INL.test(e.nodeName.toUpperCase())){e.remove();return;}while(e.attributes.length)e.removeAttribute(e.attributes[0].name);});return tp.innerHTML;}
  function trAttrs(n){ATTR.forEach(function(a){if(n.hasAttribute&&n.hasAttribute(a)){var v=n.getAttribute(a),t=trText(v);if(t!==v)n.setAttribute(a,t);}});}
  function inlineMixed(e){var el=0,tx=0;for(var c=e.firstChild;c;c=c.nextSibling){if(c.nodeType===1){if(!INL.test(c.nodeName.toUpperCase())||c.id||c.querySelector('[id]'))return 0;el=1;}else if(c.nodeType===3){if(/[A-Za-zÄÖÜäöüß]/.test(c.nodeValue))tx=1;}else if(c.nodeType!==8)return 0;}return el&&tx;}
  function walk(n){
    if(n.nodeType===3){var p=n.parentNode;if(p&&SKIP.test(p.nodeName.toUpperCase()))return;var t=trText(n.nodeValue);if(t!==n.nodeValue)n.nodeValue=t;return;}
    if(n.nodeType!==1||SKIP.test(n.nodeName.toUpperCase()))return;
    trAttrs(n);
    if(inlineMixed(n)){var v=look(norm(n.innerHTML));if(v!==undefined){n.innerHTML=safe(v);return;}}
    for(var c=n.firstChild;c;c=c.nextSibling)walk(c);
  }
  function watch(){mo.observe(document.body,{childList:true,subtree:true,characterData:true,attributes:true,attributeFilter:ATTR});}
  function onMut(ms){mo.disconnect();ms.forEach(function(m){if(m.type==='childList')m.addedNodes.forEach(walk);else if(m.type==='characterData')walk(m.target);else trAttrs(m.target);});watch();}
  function dialogs(){['confirm','prompt','alert'].forEach(function(n){var o=window[n];window[n]=function(m,d){return o.call(window,typeof m==='string'?trText(m):m,d);};});}
  function langList(){fetch('/api/lang',{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){
    var list=j.langs||[],b=document.getElementById('langBtn'),box=document.getElementById('langList');
    if(b){if(list.length||code){b.style.display='';b.textContent=code?'DE':list[0].toUpperCase();b.onclick=function(){try{if(code)localStorage.removeItem('uilang');else localStorage.setItem('uilang',list[0]);}catch(e){}location.reload();return false;};}else b.style.display='none';}
    if(box){box.textContent='';list.forEach(function(c){var d=document.createElement('div');d.className='row';var s=document.createElement('span');s.textContent=c+'.json';d.appendChild(s);
      var u=document.createElement('button');u.type='button';u.className='copy-btn';u.style.cssText='position:static;margin:2px';u.textContent='\u2716';u.title='Sprache l\u00f6schen';u.onclick=function(){if(confirm(c+'.json l\u00f6schen?'))postApi('/api/lang',{'delete':c},'langResult').then(langList);};d.appendChild(u);box.appendChild(d);});
      if(!list.length)box.textContent='Keine Sprachdatei im Ger\u00e4t';}
    if(mo&&T){mo.disconnect();if(b)walk(b);if(box)walk(box);watch();}
  }).catch(function(){});}
  window.langList=langList;
  window.langFetch=function(){var c=(document.getElementById('langCode').value||'').trim().toLowerCase().replace(/\.json$/,'');if(!c){showRes('langResult',{ok:false,error:'Keine Datei gew&auml;hlt'});return;}
    showRes('langResult',{ok:true,msg:'Lade von GitHub &hellip;'});postApi('/api/lang',{fetch:c},'langResult').then(langList);};
  window.langUpload=function(){var f=document.getElementById('langFile').files[0];if(!f){showRes('langResult',{ok:false,error:'Keine Datei gew&auml;hlt'});return;}
    var fd=new FormData();fd.append('file',f,f.name);
    fetch('/upload?target=lang',{method:'POST',body:fd}).then(function(r){return r.json();}).then(function(j){showRes('langResult',j);document.getElementById('langFile').value='';langList();}).catch(function(){showRes('langResult',{ok:false,error:'Fehler'});});};
  if(code){
    fetch('/lang.json?l='+encodeURIComponent(code),{cache:'no-cache'}).then(function(r){return r.json();}).then(function(j){
      T=j.t||{};R=(j.r||[]).map(function(x){return [new RegExp(x[0]),x[1]];});
      dialogs();mo=new MutationObserver(onMut);walk(document.body);document.title=trText(document.title);document.documentElement.lang=code;watch();langList();
    }).catch(function(){langList();});
  }else langList();
})();
)js";
static const char PAGE_JS[] PROGMEM = R"js(
function showRes(id,r){var el=document.getElementById(id);if(!el)return;
  el.className=r.ok?'res-ok':'res-bad';el.innerHTML=(r.ok?'&#10004; ':'&#10008; ')+(r.ok?(r.msg||'OK'):(r.error||'Fehler'));}
function postApi(path,params,resId){
  return fetch(path,{method:'POST',body:new URLSearchParams(params)}).then(function(r){return r.json();}).then(function(j){showRes(resId,j);return j;})
    .catch(function(){showRes(resId,{ok:false,error:'Keine Antwort vom Ger&auml;t'});});
}
var FAVS=[];
function favBtn(t,fn){var b=document.createElement('button');b.type='button';b.textContent=t;b.style.cssText='width:auto;padding:6px 12px';b.onclick=fn;return b;}
function favRow(name,url,btns){var r=document.createElement('div'),s=document.createElement('span'),i;r.setAttribute('data-url',url);s.setAttribute('data-n',name);r.className='row';r.style.justifyContent='flex-start';r.style.gap='8px';s.textContent=name;s.title=url;s.style.cssText='flex:1;text-align:left;overflow:hidden;text-overflow:ellipsis;white-space:nowrap';for(i=0;i<btns.length;i++)r.appendChild(btns[i]);r.appendChild(s);return r;}
function favMarkNow(){var u=window.NOWURL||'',rs=document.querySelectorAll('#favList .row[data-url]'),i,r,s,on;for(i=0;i<rs.length;i++){r=rs[i];s=r.querySelector('span');if(!s)continue;on=u!==''&&r.getAttribute('data-url')===u;s.style.fontWeight=on?'700':'';s.style.color=on?'var(--accent,#2a9d4a)':'';s.textContent=(on?'\u266A ':'')+s.getAttribute('data-n');}}
function favHas(u){for(var i=0;i<FAVS.length;i++)if(FAVS[i].url===u)return true;return false;}
function favRender(){var b=document.getElementById('favList'),inf=document.getElementById('favInfo');if(!b)return;b.textContent='';if(inf)inf.textContent=FAVS.length+' Favoriten';
  FAVS.forEach(function(f){b.appendChild(favRow(f.name,f.url,[favBtn('▶',function(){postApi('/api/play',{url:f.url},'favResult');}),favBtn('API',function(){favCall(f,this);}),favDelBtn(f)]));});
  favMarkNow();}
function favLoad(){fetch('/api/favorites',{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){FAVS=j.favorites||[];favRender();}).catch(function(){});}
function loadFavorites(inp){var f=inp.files[0];if(!f)return;if(!confirm('Die Favoriten werden durch die Datei ersetzt. Fortfahren?')){inp.value='';return;}
  var rd=new FileReader();rd.onload=function(){fetch('/importfavorites',{method:'POST',headers:{'Content-Type':'text/plain'},body:rd.result}).then(function(r){return r.text();}).then(function(t){
    showRes('favResult',t.indexOf('OK|')===0?{ok:true,msg:t.substring(3)}:{ok:false,error:t.substring(5)});inp.value='';favLoad();});};rd.readAsText(f);}
function favAddStation(n){var a=document.querySelector("input[name='rn"+n+"']"),u=document.querySelector("input[name='ru"+n+"']");if(u&&u.value)favAdd(a?a.value:"",u.value);}
function favAdd(name,url){postApi('/api/favoriteadd',{name:name,url:url},'favResult').then(favLoad);}
function favDelBtn(f){return favBtn('✕',function(){favDel(f);});}
function favDel(f){if(!confirm('Favorit "'+f.name+'" löschen?'))return;postApi('/api/favoritedelete',{n:f.n},'favResult').then(favLoad);}
function favToList(){if(!confirm('Die gespeicherte Senderliste wird durch die Favoriten ersetzt. Fortfahren?'))return;postApi('/api/favoritestolist',{},'favResult').then(function(j){if(j&&j.ok)setTimeout(function(){location.href='/?tab=radio';},1200);});}
function listFill(t,en){var s=document.getElementById('stList'),ls=(t||'').split(/\r?\n/),opts=[],i,p,o,keep;if(!s)return 0;
  for(i=0;i<ls.length;i++){p=ls[i].split('|');if(!/^[a-z0-9-]+$/.test(p[0]||''))continue;opts.push([p[0],p[0]+' – '+((en?p[2]:p[1])||'')]);}
  if(!opts.length)return 0;keep=s.value;s.textContent='';
  for(i=0;i<opts.length;i++){o=document.createElement('option');o.value=opts[i][0];o.textContent=opts[i][1];s.appendChild(o);}
  if(keep)s.value=keep;if(s.selectedIndex<0)s.selectedIndex=0;return opts.length;}
function listIndex(tryNo){tryNo=tryNo||0;var c='',cached='';try{c=localStorage.getItem('uilang')||'';}catch(e){}var en=c?c.indexOf('en')===0:!/^de/i.test(navigator.language||'de');
  function again(){if(tryNo<3)setTimeout(function(){listIndex(tryNo+1);},3000*(tryNo+1));}
  if(!tryNo){try{cached=localStorage.getItem('stidx')||'';}catch(e){}if(cached)listFill(cached,en);}
  fetch('https://raw.githubusercontent.com/holgiw/ESP32-netspeaker/main/stations/index.txt',{cache:'no-store'}).then(function(r){return r.ok?r.text():'';}).then(function(t){
    if(t&&listFill(t,en)){try{localStorage.setItem('stidx',t);}catch(e){}}else again();}).catch(again);}
var RB_CODES=['DE','AT','CH','LI','LU','BE','NL','FR','IT','ES','PT','GB','IE','IS','NO','SE','DK','FI','EE','LV','LT','PL','CZ','SK','HU','SI','HR','BA','RS','ME','MK','AL','BG','RO','MD','UA','BY','RU','GR','CY','MT','TR','IL','EG','MA','TN','DZ','ZA','NG','KE','AE','SA','IN','PK','BD','LK','TH','VN','MY','SG','ID','PH','JP','KR','CN','TW','HK','AU','NZ','US','CA','MX','CO','VE','PE','CL','AR','UY','BR','CU','DO','PR','CR','PA'];
var RB_SERVERS=['https://de1.api.radio-browser.info','https://de2.api.radio-browser.info','https://fi1.api.radio-browser.info','https://nl1.api.radio-browser.info'];
var RB_BAD=/news|nachricht|noticias|actualit|cnn|bbc world|quran|koran|bible|gospel|church|kirche|jesus|islam|christmas|weihnacht|halloween|sport|parliament|parlament/i;
function rbInit(){var s=document.getElementById('rbCountry');if(!s)return;var lang=navigator.language||'de-DE',reg=(lang.split('-')[1]||'').toUpperCase(),dn=null,i,o,arr=[];
  try{dn=new Intl.DisplayNames([lang],{type:'region'});}catch(e){}
  for(i=0;i<RB_CODES.length;i++){var nm=RB_CODES[i];try{if(dn)nm=dn.of(RB_CODES[i])||nm;}catch(e){}arr.push([RB_CODES[i],nm]);}
  arr.sort(function(a,b){return a[1].localeCompare(b[1],lang);});
  for(i=0;i<arr.length;i++){o=document.createElement('option');o.value=arr[i][0];o.textContent=arr[i][1]+' ('+arr[i][0]+')';s.appendChild(o);}
  s.value=RB_CODES.indexOf(reg)>=0?reg:'DE';}
function rbCut(s,max){var b=new TextEncoder().encode(s);if(b.length<=max)return s;var cut=max;while(cut>0&&(b[cut]&192)===128)cut--;var t=new TextDecoder('utf-8').decode(b.slice(0,cut)),m=t.match(/^(.+)\s\S*$/);return(m&&m[1].length>=8?m[1]:t).trim();}
function rbName(n,u){var h='Radio';try{h=new URL(u).hostname;}catch(e){}n=(n||'').replace(/[\x00-\x1f=]+/g,' ').replace(/^[-_\s*#.]+|[-_\s*]+$/g,'').replace(/\s+/g,' ').trim();if(n.length<3)n=h;return rbCut(n,24).replace(/[-_\s*|(\[]+$/,'');}
function rbBuild(list){var su={},sn={},out=[],i,s,u,n,k;
  for(i=0;i<list.length&&out.length<30;i++){s=list[i];if(!s||s.lastcheckok!==1)continue;u=s.url_resolved||s.url||'';
    if(!/^https?:\/\//i.test(u)||u.length>200||/\.(m3u8?|pls)(\?|$)|token=|[?&]time=|sid=|cid=|\.php/i.test(u))continue;
    if(!/^(mp3|aac\+?)$/i.test(s.codec||''))continue;n=rbName(s.name,u);if(RB_BAD.test(n))continue;
    k=n.toLowerCase().replace(/[^a-z0-9]/g,'')||n;if(su[u]||sn[k])continue;su[u]=1;sn[k]=1;out.push([n,u]);}
  return out;}
function rbFetch(q,i){if(i>=RB_SERVERS.length)return Promise.reject(new Error('radio-browser'));
  return fetch(RB_SERVERS[i]+'/json/stations/search?'+q,{cache:'no-store'}).then(function(r){if(!r.ok)throw 0;return r.json();}).catch(function(){return rbFetch(q,i+1);});}
function rbLoad(){var c=document.getElementById('rbCountry').value,g=document.getElementById('rbGenre').value;if(!c)return;
  if(!confirm('Die gespeicherte Senderliste wird durch Sender aus radio-browser ersetzt. Fortfahren?'))return;
  showRes('stListResult',{ok:true,msg:'Lade von radio-browser &hellip;'});
  rbFetch('countrycode='+encodeURIComponent(c)+(g?'&tag='+encodeURIComponent(g):'')+'&hidebroken=true&order=clickcount&reverse=true&limit=300',0).then(function(list){
    var st=rbBuild(list),t='# netspeaker stations\n',i;
    if(!st.length){showRes('stListResult',{ok:false,error:'Keine passenden Sender gefunden'});return;}
    for(i=0;i<st.length;i++)t+='rn'+(i+1)+'='+st[i][0]+'\nru'+(i+1)+'='+st[i][1]+'\nrv'+(i+1)+'=\n';
    return fetch('/importstations',{method:'POST',headers:{'Content-Type':'text/plain'},body:t}).then(function(r){return r.text();}).then(function(x){
      if(x.indexOf('OK|')===0){showRes('stListResult',{ok:true,msg:x.substring(3)});setTimeout(function(){location.href='/?tab=radio';},1500);}
      else showRes('stListResult',{ok:false,error:x.substring(5)});});
  }).catch(function(){showRes('stListResult',{ok:false,error:'radio-browser nicht erreichbar'});});}
function listFetch(){var n=(document.getElementById('stList').value||'').trim();if(!n)return;if(!confirm('Die gespeicherte Senderliste wird durch die Liste von GitHub ersetzt. Fortfahren?'))return;showRes('stListResult',{ok:true,msg:'Lade von GitHub &hellip;'});postApi('/api/stationlist',{list:n},'stListResult').then(function(j){if(j&&j.ok)setTimeout(function(){location.href='/?tab=radio';},1200);});}
var VOICE_TEXT={'de-de':'Hallo, das ist ein Test dieser Stimme.','en-gb':'Hello, this is a test of this voice.','en-us':'Hello, this is a test of this voice.','fr-fr':'Bonjour, ceci est un test de cette voix.','es-es':'Hola, esta es una prueba de esta voz.','it-it':'Ciao, questo è un test di questa voce.','nl-nl':'Hallo, dit is een test van deze stem.','pt-pt':'Olá, este é um teste desta voz.','pl-pl':'Cześć, to jest test tego głosu.','sv-se':'Hej, det här är ett test av den här rösten.','da-dk':'Hej, dette er en test af denne stemme.'};
function ttsInfo(){fetch('/api/ttscache',{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){var e=document.getElementById('ttsInfo');if(e)e.textContent=j.files+' Dateien, '+Math.round(j.bytes/1024)+' KB';}).catch(function(){});}
function ttsClear(){if(!confirm('Alle zwischengespeicherten Ansagen von der SD-Karte l\u00f6schen?'))return;postApi('/api/ttscache',{clear:1},'ttsResult').then(ttsInfo);}
function voiceTest(){var l=document.getElementById('cfgLang').value||DEF_LANG,v=document.getElementById('cfgVoice').value,r=document.querySelector("input[name='vrate']").value;if(v==='__custom__')v='';postApi('/api/say',{text:VOICE_TEXT[l]||VOICE_TEXT['en-gb'],lang:l,voice:v,rate:r},'voiceTestResult');}
function fxSend(){var g=function(i){return document.getElementById(i);};postApi('/api/effect',{mode:g('fxMode').value,wet:g('fxWet').value,bass:g('eqBass').value,treble:g('eqTreble').value,pan:g('fxPan').value,pansec:g('fxPanSec').value},'fxResult');}
var BK=null;
function bkCrcTable(){var t=[],c,n,k;for(n=0;n<256;n++){c=n;for(k=0;k<8;k++)c=c&1?(0xEDB88320^(c>>>1)):(c>>>1);t[n]=c>>>0;}return t;}
var BKCRC=bkCrcTable();
function bkCrc(b){var c=0xFFFFFFFF,i;for(i=0;i<b.length;i++)c=BKCRC[(c^b[i])&255]^(c>>>8);return (c^0xFFFFFFFF)>>>0;}
function bkZip(entries){var enc=new TextEncoder(),parts=[],cd=[],off=0,d=new Date(),dt=((d.getHours()<<11)|(d.getMinutes()<<5)|(d.getSeconds()>>1)),dd=(((d.getFullYear()-1980)<<9)|((d.getMonth()+1)<<5)|d.getDate());
  function u16(v){return [v&255,(v>>8)&255];}function u32(v){return [v&255,(v>>8)&255,(v>>16)&255,(v>>>24)&255];}
  entries.forEach(function(e){var nb=enc.encode(e.name),crc=bkCrc(e.data),sz=e.data.length;
    var lh=[].concat(u32(0x04034b50),u16(20),u16(0x0800),u16(0),u16(dt),u16(dd),u32(crc),u32(sz),u32(sz),u16(nb.length),u16(0));
    parts.push(new Uint8Array(lh),nb,e.data);
    cd.push({nb:nb,crc:crc,sz:sz,off:off});off+=lh.length+nb.length+sz;});
  var cdStart=off,cdSize=0;
  cd.forEach(function(c){var h=[].concat(u32(0x02014b50),u16(20),u16(20),u16(0x0800),u16(0),u16(dt),u16(dd),u32(c.crc),u32(c.sz),u32(c.sz),u16(c.nb.length),u16(0),u16(0),u16(0),u16(0),u32(0),u32(c.off));
    parts.push(new Uint8Array(h),c.nb);cdSize+=h.length+c.nb.length;});
  parts.push(new Uint8Array([].concat(u32(0x06054b50),u16(0),u16(0),u16(cd.length),u16(cd.length),u32(cdSize),u32(cdStart),u16(0))));
  return new Blob(parts,{type:'application/zip'});}
function bkUnzip(buf){var v=new DataView(buf),u=new Uint8Array(buf),off=0,out=[],dec=new TextDecoder();
  while(off+30<=buf.byteLength&&v.getUint32(off,true)===0x04034b50){var fl=v.getUint16(off+6,true),me=v.getUint16(off+8,true),cs=v.getUint32(off+18,true),nl=v.getUint16(off+26,true),el=v.getUint16(off+28,true);
    if(me!==0||(fl&8))throw new Error('zip');
    var name=dec.decode(u.subarray(off+30,off+30+nl)),st=off+30+nl+el;out.push({name:name,data:u.subarray(st,st+cs)});off=st+cs;}
  return out;}
function bkSave(blob,name){var a=document.createElement('a');a.href=URL.createObjectURL(blob);a.download=name;document.body.appendChild(a);a.click();setTimeout(function(){URL.revokeObjectURL(a.href);a.remove();},2000);}
function bkChk(id){var e=document.getElementById(id);return !!(e&&e.checked);}
function bkFilesInfo(){fetch('/api/files',{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){var n=(j.files||[]).length,b=0;(j.files||[]).forEach(function(f){b+=f.size;});var e=document.getElementById('bkFilesInfo');if(e)e.textContent='('+n+' Dateien, '+Math.round(b/1024)+' KB)';}).catch(function(){});}
function bkCreate(){var wifi=bkChk('bkWifi'),files=bkChk('bkFiles'),base=(window.UI_HOST||'netspeaker');
  showRes('bkResult',{ok:true,msg:'Erstelle Sicherung &hellip;'});
  fetch('/export'+(wifi?'?wifi=1':''),{cache:'no-store'}).then(function(r){return r.text();}).then(function(txt){
    if(!files){bkSave(new Blob([txt],{type:'text/plain'}),base+'-settings.txt');showRes('bkResult',{ok:true,msg:'Sicherung erstellt'});return;}
    var enc=new TextEncoder(),ents=[{name:'settings.txt',data:enc.encode(txt)}];
    return fetch('/api/files',{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){var list=j.files||[];
      return list.reduce(function(p,f,i){return p.then(function(){showRes('bkResult',{ok:true,msg:'Lade Datei '+(i+1)+' von '+list.length+' &hellip;'});
        return fetch('/api/fileget?file='+encodeURIComponent(f.name),{cache:'no-store'}).then(function(r){if(!r.ok)throw new Error(f.name);return r.arrayBuffer();}).then(function(ab){ents.push({name:'mp3/'+f.name,data:new Uint8Array(ab)});});});},Promise.resolve())
      .then(function(){bkSave(bkZip(ents),base+'-backup.zip');showRes('bkResult',{ok:true,msg:'Sicherung erstellt ('+list.length+' Dateien)'});});});
  }).catch(function(e){showRes('bkResult',{ok:false,error:'Sicherung fehlgeschlagen'});});}
function bkPick(){var inp=document.getElementById('bkFile'),f=inp.files[0],info=document.getElementById('bkInfo'),btn=document.getElementById('bkRestoreBtn');BK=null;btn.disabled=true;
  document.getElementById('bkImpWifi').disabled=true;document.getElementById('bkImpFiles').disabled=true;document.getElementById('bkImpWifi').checked=false;document.getElementById('bkImpFiles').checked=false;info.textContent='';
  if(!f)return;
  function ready(settings,files){if(settings.indexOf('# netspeaker settings export')!==0){showRes('bkRestoreResult',{ok:false,error:'Das ist keine Sicherung dieses Ger\u00e4ts'});return;}
    var hasWifi=/^pass[123]=/m.test(settings),n=files.length,b=0;files.forEach(function(x){b+=x.data.length;});BK={settings:settings,files:files};
    info.textContent='Einstellungen: ja; WLAN-Passw\u00f6rter: '+(hasWifi?'ja':'nein')+'; Dateien im Flash: '+n+(n?' ('+Math.round(b/1024)+' KB)':'');
    document.getElementById('bkImpWifi').disabled=false;
    if(n){document.getElementById('bkImpFiles').disabled=false;document.getElementById('bkImpFiles').checked=true;}
    btn.disabled=false;document.getElementById('bkRestoreResult').innerHTML='';}
  if(/\.zip$/i.test(f.name)){f.arrayBuffer().then(function(ab){var ents;try{ents=bkUnzip(ab);}catch(e){showRes('bkRestoreResult',{ok:false,error:'ZIP-Datei nicht lesbar (nur unkomprimierte Sicherungen dieses Ger\u00e4ts)'});return;}
      var st=null,fl=[];ents.forEach(function(e){if(e.name==='settings.txt')st=new TextDecoder().decode(e.data);else if(/^mp3\/(ansagen\/)?[^\/]+\.mp3$/i.test(e.name))fl.push({name:e.name.substring(4),data:e.data});});
      if(st===null){showRes('bkRestoreResult',{ok:false,error:'Keine Einstellungen in der ZIP-Datei'});return;}ready(st,fl);});}
  else f.text().then(function(t){ready(t,[]);});}
function bkRestore(){if(!BK)return;var wifi=bkChk('bkImpWifi'),files=bkChk('bkImpFiles')&&BK.files.length>0,st=BK.settings;
  if(!confirm('Bestehende Einstellungen werden \u00fcberschrieben'+(files?' und Dateien gleichen Namens ersetzt':'')+'. Fortfahren?'))return;
  if(!wifi)st=st.split('\n').filter(function(l){return !/^(ssid|pass)[123]=/.test(l);}).join('\n');
  showRes('bkRestoreResult',{ok:true,msg:'Lese Einstellungen ein &hellip;'});
  fetch('/import',{method:'POST',headers:{'Content-Type':'text/plain'},body:st}).then(function(r){return r.text();}).then(function(t){
    if(t.indexOf('OK|')!==0){showRes('bkRestoreResult',{ok:false,error:t.indexOf('FAIL|')===0?t.substring(5):'Fehler'});return;}
    var msg=t.substring(3),bad=[];
    if(!files){showRes('bkRestoreResult',{ok:true,msg:msg});return;}
    return BK.files.reduce(function(p,f,i){return p.then(function(){showRes('bkRestoreResult',{ok:true,msg:'Lade Datei '+(i+1)+' von '+BK.files.length+' hoch &hellip;'});
      var sub=f.name.indexOf('ansagen/')===0,fd=new FormData();fd.append('file',new Blob([f.data],{type:'audio/mpeg'}),sub?f.name.substring(8):f.name);
      return fetch('/upload'+(sub?'?dir=ansagen':''),{method:'POST',body:fd}).then(function(r){return r.json();}).then(function(j){if(!j.ok)bad.push(f.name);}).catch(function(){bad.push(f.name);});});},Promise.resolve())
    .then(function(){showRes('bkRestoreResult',bad.length?{ok:false,error:msg+' Dateien: '+(BK.files.length-bad.length)+' von '+BK.files.length+' eingelesen; Fehler: '+bad.join(', ')}:{ok:true,msg:msg+' '+BK.files.length+' Dateien eingelesen.'});bkFilesInfo();});
  }).catch(function(){showRes('bkRestoreResult',{ok:false,error:'Keine Antwort vom Ger&auml;t'});});}
function sayNow(){var sv=document.getElementById('saySave');var want=sv&&sv.checked;postApi('/api/say',{text:document.getElementById('sayText').value,lang:document.getElementById('sayLang').value,voice:document.getElementById('sayVoice').value,save:want?1:0},'sayResult').then(function(j){if(j&&j.ok&&want)saveWait();});}
function saveWait(){var seq0=SAYSEQ,t0=Date.now(),off=0,started=false,tm=setInterval(function(){if(Date.now()-t0>90000){clearInterval(tm);return;}
  fetch('/api/status',{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){
    if(j.speechSeq>seq0)started=true;
    if(started&&!j.speechOn&&j.source!=='speech'){off++;if(off>=2){clearInterval(tm);var sv=document.getElementById('saySave');if(sv)sv.checked=false;}}else off=0;
  }).catch(function(){});},500);}
function clearLog(){if(!confirm('Log l\u00f6schen?'))return;postApi('/api/log',{clear:'1'},'logResult').then(function(){var p=document.getElementById('logContent');if(p)p.textContent='';});}
function copyText(t,btn){
  function done(ok){if(btn){var o=btn.getAttribute('data-o')||btn.textContent;btn.setAttribute('data-o',o);btn.textContent=ok?'Kopiert':'Fehler';setTimeout(function(){btn.textContent=o;},1500);}}
  if(navigator.clipboard&&window.isSecureContext){navigator.clipboard.writeText(t).then(function(){done(true);},function(){done(false);});return;}
  var ta=document.createElement('textarea');ta.value=t;ta.style.position='fixed';ta.style.opacity='0';document.body.appendChild(ta);ta.select();
  var ok=false;try{ok=document.execCommand('copy');}catch(e){}document.body.removeChild(ta);done(ok);}
function copyPre(btn){copyText(btn.parentNode.querySelector('pre').textContent,btn);}
function playStation(n){postApi('/api/station',{n:n},'stResult');}
function moveStation(n,d){var a=document.querySelector('.stationrow[data-n="'+n+'"]'),b=document.querySelector('.stationrow[data-n="'+(n+d)+'"]');if(!a||!b||!b.getAttribute('data-url')&&d>0)return;['rn','ru','rv'].forEach(function(p){var x=a.querySelector('[name="'+p+n+'"]'),y=b.querySelector('[name="'+p+(n+d)+'"]'),t=x.value;x.value=y.value;y.value=t;});a.closest('form').submit();}
function delStation(n){if(!confirm('Platz '+n+' (Name und URL) l\u00f6schen?'))return;postApi('/api/stationdelete',{n:n},'stResult').then(function(j){if(j&&j.ok)location.href='/?tab=radio';});}
function stationLink(n){return location.origin+'/api/station?n='+n+'&vol=60';}
function callLine(box,label,text){var d=document.createElement('div'),c=document.createElement('code'),b=document.createElement('button');d.style.cssText='display:flex;gap:8px;align-items:center;margin:2px 0';d.appendChild(document.createTextNode(label+' '));c.textContent=text;c.style.flex='1';b.type='button';b.textContent='Kopieren';b.className='copy-btn';b.style.cssText='position:static;margin:0';b.onclick=function(){copyText(text,b);};d.appendChild(c);d.appendChild(b);box.appendChild(d);}
function callBox(row,lines){var old=row.nextSibling;if(old&&old.className==='callbox'){old.remove();return;}var b=document.createElement('div'),i;b.className='callbox';b.style.cssText='margin:0 0 8px 2rem;padding:6px 10px;border:1px solid var(--panel-border);border-radius:6px;text-align:left;font-size:.85em;overflow-wrap:anywhere';
  for(i=0;i<lines.length;i++)callLine(b,lines[i][0],lines[i][1]);if(!MQTT_ON){var s=document.createElement('small');s.textContent='MQTT: Broker im Tab MQTT eintragen.';b.appendChild(s);}row.parentNode.insertBefore(b,row.nextSibling);}
function stationCall(n,btn){var row=btn.closest('.stationrow'),nm=row?(row.querySelector("input[name='rn"+n+"']")||{}).value:'';callBox(row,[['REST:',location.origin+'/api/station?n='+n+'&vol=60'],nm?['REST (Name):',location.origin+'/api/station?name='+encodeURIComponent(nm)+'&vol=60']:null,['MQTT Thema:',MQTT_BASE+'/station'],['MQTT Nutzlast:',String(n)],['MQTT Nutzlast (JSON):','{"n":'+n+',"vol":60}']].filter(Boolean));}
function favCall(f,btn){callBox(btn.parentNode,[['REST:','curl -d "url='+f.url+'&vol=60" '+location.origin+'/api/play'],['MQTT Thema:',MQTT_BASE+'/play'],['MQTT Nutzlast:',f.url],['MQTT Nutzlast (JSON):','{"url":"'+f.url+'","vol":60}']]);}
function apiLink(n){return location.origin+'/api/file?file='+encodeURIComponent(n)+'&vol=60&shuffle=0&loop=0&pan=off&pansec=3';}
var VOICES={'de-de':['Hanna','Lina','Jonas'],'en-gb':['Alice','Nancy','Lily','Harry'],'en-us':['Linda','Amy','Mary','John','Mike'],'fr-fr':['Bette','Iva','Zola'],'es-es':['Camila','Sofia','Luna'],'it-it':['Bria','Mia','Pietro'],'pl-pl':['Julia','Jan'],'sv-se':['Molly','Hugo']};
function fillVoiceSel(id,lang,keep){var s=document.getElementById(id);if(!s)return;var cur=s.value;var v=VOICES[lang||DEF_LANG]||[];s.innerHTML='';
  function add(val,txt){var o=document.createElement('option');o.value=val;o.textContent=txt;s.appendChild(o);}
  add('','Standard (VoiceRSS)');v.forEach(function(n){add(n,n);});
  if(keep&&cur&&cur!=='__custom__'&&v.indexOf(cur)<0)add(cur,cur);
  add('__custom__','Andere \u2026');
  s.value=((keep||v.indexOf(cur)>=0)&&cur!=='__custom__')?cur:'';}
function voiceChosen(s){if(s.value!=='__custom__')return;
  var n=(prompt('Name der Stimme (wie bei VoiceRSS):')||'').replace(/[^A-Za-z0-9_-]/g,'');
  if(!n){s.value='';return;}
  var o=document.createElement('option');o.value=n;o.textContent=n;s.insertBefore(o,s.querySelector('option[value="__custom__"]'));s.value=n;}function muteShow(m){document.querySelectorAll('.mutebtn').forEach(function(b){b.textContent=m?'Ton an':'Stumm';b.style.opacity=m?'0.75':'';b.style.outline=m?'2px solid var(--accent,#f4a02a)':'';});}
function muteToggle(){fetch('/api/mute',{method:'POST',body:new URLSearchParams({toggle:'1'})}).then(function(r){return r.json();}).then(function(j){muteShow(!!j.muted);}).catch(function(){});}
function stopNow(){postApi('/api/stop',{},'sayResult');}
function volShow(v){var s=document.querySelectorAll('.volrange'),e=document.querySelectorAll('.volshow'),i;for(i=0;i<s.length;i++){if(+s[i].value!==+v)s[i].value=v;}for(i=0;i<e.length;i++)e[i].textContent=v+' / '+(s[0]?s[0].max:100);}
function setVol(v){volShow(v);fetch('/api/volume',{method:'POST',body:new URLSearchParams({v:v})});}
function playUrlNow(){postApi('/api/play',{url:document.getElementById('playUrl').value},'radioResult');}
var sdCur='/';
function checkPins(){var s=document.querySelectorAll('select.pinsel'),seen={},dup=false;s.forEach(function(e){e.classList.remove('dup');});
  s.forEach(function(e){var v=e.value;if(seen[v]){seen[v].classList.add('dup');e.classList.add('dup');dup=true;}else seen[v]=e;});
  var w=document.getElementById('pinWarn');if(w)w.textContent=dup?'Ein Pin ist doppelt vergeben; so werden die Pins nicht gespeichert.':'';}
function memShow(id,used,total){var e=document.getElementById(id);if(!e)return;e.textContent='';if(!(total>0))return;
  var u=total<10485760?['KB',1024]:(total<10737418240?['MB',1048576]:['GB',1073741824]),pct=Math.round(100*used/total);
  var s=document.createElement('small');s.textContent='Belegt '+Math.round(used/u[1])+' von '+Math.round(total/u[1])+' '+u[0]+' ('+pct+' %)';
  var bar=document.createElement('div');bar.style.cssText='height:6px;margin:4px 0 8px;background:#3a4147;border-radius:3px;overflow:hidden';
  var f=document.createElement('div');f.style.cssText='height:100%;background:var(--ok);width:'+Math.min(100,pct)+'%';bar.appendChild(f);e.appendChild(s);e.appendChild(bar);}
function sdLoad(dir){var box=document.getElementById('sdList');if(!box)return;dir=dir||'/';
  fetch('/api/sd?dir='+encodeURIComponent(dir),{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){
    var info=document.getElementById('sdInfo'),pth=document.getElementById('sdPath');box.textContent='';sdCur=j.dir||'/';
    if(!j.mounted){info.textContent=j.state==='off'?'SD-Karte ist ausgeschaltet (Tab Audio)':'Keine Karte gefunden';pth.textContent='';memShow('sdMem',0,0);return;}
    info.textContent='Karte '+j.state;memShow('sdMem',j.used*1048576,j.size*1048576);pth.textContent=j.dir;
    var cur=j.dir==='/'?'':j.dir,tb=document.createElement('table');tb.style.width='100%';
    function cell(tr,t){var td=document.createElement('td');if(t!==null)td.textContent=t;tr.appendChild(td);return td;}
    function btn(td,txt,tip,fn){var b=document.createElement('button');b.type='button';b.className='copy-btn';b.style.cssText='position:static;margin:2px';b.textContent=txt;b.title=tip;b.onclick=fn;td.appendChild(b);}
    function cp(td,n){btn(td,'URL',apiLink(n),function(){copyText(apiLink(n),this);});btn(td,'curl','curl-Aufruf kopieren',function(){copyText('curl "'+apiLink(n)+'"',this);});}
    function dl(td,p){var a=document.createElement('a');a.className='copy-btn';a.style.cssText='position:static;margin:2px;display:inline-block;text-decoration:none';a.textContent='\u2B07';a.title='Datei herunterladen';a.href='/api/sdfile?path='+encodeURIComponent(p);td.appendChild(a);}
    if(j.dir!=='/'){var up=document.createElement('tr'),ut=cell(up,null),ua=document.createElement('a');ua.href='#';ua.textContent='\u2191 ..';ua.onclick=function(){sdLoad(j.dir.replace(/\/[^\/]*$/,'')||'/');return false;};ut.appendChild(ua);cell(up,'');cell(up,'');tb.appendChild(up);}
    if(j.entries.some(function(e){return !e.d;})){var hr=document.createElement('tr'),hc=cell(hr,null),ha;hc.textContent=j.dir==='/'?'📁 / (Hauptverzeichnis)':'📁 dieser Ordner';cell(hr,'');ha=cell(hr,null);
      btn(ha,'▶ Ordner','Alle MP3-Dateien dieses Ordners nacheinander abspielen',function(){playFile('sd:'+cur+'/','sdResult',{loop:sdLoopOn()});});
      btn(ha,'🔀 Zufall','Alle MP3-Dateien dieses Ordners in zufälliger Reihenfolge abspielen, jede einmal je Sitzung',function(){playFile('sd:'+cur+'/','sdResult',{shuffle:1,loop:sdLoopOn()});});
      cp(ha,'sd:'+cur+'/');
      tb.appendChild(hr);}
    j.entries.forEach(function(e){var tr=document.createElement('tr'),td=cell(tr,null),p=cur+'/'+e.n,act;
      if(e.d){var a=document.createElement('a');a.href='#';a.textContent='\uD83D\uDCC1 '+e.n;a.onclick=function(){sdLoad(p);return false;};td.appendChild(a);cell(tr,'');act=cell(tr,null);
        btn(act,'\u25B6 Ordner','Alle MP3-Dateien des Ordners nacheinander abspielen',function(){playFile('sd:'+p+'/','sdResult',{loop:sdLoopOn()});});
        btn(act,'\uD83D\uDD00 Zufall','Alle MP3-Dateien des Ordners in zuf\u00e4lliger Reihenfolge abspielen, jede einmal je Sitzung',function(){playFile('sd:'+p+'/','sdResult',{shuffle:1,loop:sdLoopOn()});});cp(act,'sd:'+p+'/');}
      else{td.textContent=e.n;cell(tr,Math.round(e.s/1024)+' KB');act=cell(tr,null);
        btn(act,'\u25B6','Abspielen (reiht sich in die Warteschlange ein)',function(){playFile('sd:'+p,'sdResult');});dl(act,p);cp(act,'sd:'+p);}
      btn(act,'\u270E','Umbenennen',function(){sdRen(p,e.n,e.d);});
      btn(act,'\u2716',e.d?'Ordner mit Inhalt l\u00f6schen':'Datei l\u00f6schen',function(){sdDel(p,e.d);});
      tb.appendChild(tr);});
    if(!j.entries.length)tb.appendChild(document.createElement('tr')).appendChild(document.createElement('td')).textContent='Keine MP3-Dateien oder Ordner';
    box.appendChild(tb);}).catch(function(){});}
function sdRemount(){postApi('/api/sdmount',{},'sdResult').then(function(){sdLoad('/');});}
function sdMkdir(){var n=prompt('Name des neuen Ordners:');if(!n)return;postApi('/api/sdmkdir',{dir:sdCur,name:n},'sdResult').then(function(){sdLoad(sdCur);});}
function sdDel(p,isDir){if(!confirm((isDir?'Ordner mit allem Inhalt ':'Datei ')+p+' l\u00f6schen?'))return;postApi('/api/sddelete',{path:p},'sdResult').then(function(){sdLoad(sdCur);});}
function sdRen(p,old,isDir){var n=prompt('Neuer Name:',old);if(!n||n===old)return;postApi('/api/sdrename',{path:p,to:n},'sdResult').then(function(){sdLoad(sdCur);});}
function sdUploadNow(){var fs=Array.prototype.slice.call(document.getElementById('sdUpFile').files);if(!fs.length){showRes('sdResult',{ok:false,error:'Keine Datei gew&auml;hlt'});return;}
  var i=0,okc=0,bad=[];
  function next(){if(i>=fs.length){document.getElementById('sdUpFile').value='';sdLoad(sdCur);
      showRes('sdResult',bad.length?{ok:false,error:okc+' von '+fs.length+' hochgeladen; Fehler: '+bad.join(', ')}:{ok:true,msg:okc+(okc==1?' Datei':' Dateien')+' hochgeladen'});return;}
    var f=fs[i],fn=f.name.replace(/[<>&"']/g,'_');showRes('sdResult',{ok:true,msg:'Lade hoch ('+(i+1)+'/'+fs.length+'): '+fn+' &hellip;'});
    var fd=new FormData();fd.append('file',f,f.name);
    fetch('/upload?target=sd&dir='+encodeURIComponent(sdCur),{method:'POST',body:fd}).then(function(r){return r.json();}).then(function(j){if(j&&j.ok)okc++;else bad.push(fn+' ('+((j&&j.error)||'Fehler')+')');})
      .catch(function(){bad.push(fn);}).then(function(){i++;next();});}
  next();}
function playFile(n,res,ex){var p={file:n};if(ex)for(var k in ex)p[k]=ex[k];postApi('/api/play',p,res||'upResult');}
function sdLoopOn(){var c=document.getElementById('sdLoop');return c&&c.checked?'1':'0';}
function renFile(n){var x=prompt('Neuer Name:',n);if(!x||x===n)return;postApi('/api/rename',{file:n,to:x},'upResult').then(function(){loadFiles();});}
function delFile(n){if(!confirm('Datei '+n+' löschen?'))return;postApi('/api/delete',{file:n},'upResult').then(function(){loadFiles();});}
var fsCur='';
function loadFiles(dir){if(dir===undefined)dir=fsCur;fsCur=dir;var box=document.getElementById('fileList');if(!box)return;
  fetch('/api/flash?dir='+encodeURIComponent(dir),{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){
    box.textContent='';memShow('fsMem',j.used,j.total);
    var pre=dir?dir+'/':'',tb=document.createElement('table');tb.style.width='100%';
    function cell(tr,t){var td=document.createElement('td');if(t!==null)td.textContent=t;tr.appendChild(td);return td;}
    function btn(td,txt,tip,fn){var b=document.createElement('button');b.type='button';b.className='copy-btn';b.style.cssText='position:static;margin:2px';b.textContent=txt;b.title=tip;b.onclick=fn;td.appendChild(b);}
    function cp(td,n){btn(td,'URL',apiLink(n),function(){copyText(apiLink(n),this);});btn(td,'curl','curl-Aufruf kopieren',function(){copyText('curl "'+apiLink(n)+'"',this);});}
    function dl(td,n){var a=document.createElement('a');a.className='copy-btn';a.style.cssText='position:static;margin:2px;display:inline-block;text-decoration:none';a.textContent='\u2B07';a.title='Datei herunterladen';a.href='/api/fileget?file='+encodeURIComponent(n);a.setAttribute('download',n.replace(/^.*\//,''));td.appendChild(a);}
    if(dir){var up=document.createElement('tr'),ut=cell(up,null),ua=document.createElement('a');ua.href='#';ua.textContent='\u2191 ..';ua.onclick=function(){loadFiles('');return false;};ut.appendChild(ua);cell(up,'');cell(up,'');tb.appendChild(up);}
    if(j.entries.some(function(e){return !e.d;})){var hr=document.createElement('tr'),hc=cell(hr,null),ha;hc.textContent=dir?'\uD83D\uDCC1 dieser Ordner':'\uD83D\uDCC1 / (Hauptverzeichnis)';cell(hr,'');ha=cell(hr,null);var ref=dir?dir+'/':'/';
      btn(ha,'\u25B6 Ordner','Alle MP3-Dateien dieses Ordners nacheinander abspielen',function(){playFile(ref,'upResult');});
      btn(ha,'\uD83D\uDD00 Zufall','Alle MP3-Dateien dieses Ordners in zuf\u00e4lliger Reihenfolge abspielen, jede einmal je Sitzung',function(){playFile(ref,'upResult',{shuffle:1});});
      cp(ha,ref);tb.appendChild(hr);}
    j.entries.forEach(function(e){var tr=document.createElement('tr'),td=cell(tr,null),n=pre+e.n,act;
      if(e.d){var a=document.createElement('a');a.href='#';a.textContent='\uD83D\uDCC1 '+e.n;a.onclick=function(){loadFiles(e.n);return false;};td.appendChild(a);cell(tr,'');act=cell(tr,null);
        btn(act,'\u25B6 Ordner','Alle MP3-Dateien des Ordners nacheinander abspielen',function(){playFile(e.n+'/','upResult');});
        btn(act,'\uD83D\uDD00 Zufall','Alle MP3-Dateien des Ordners in zuf\u00e4lliger Reihenfolge abspielen, jede einmal je Sitzung',function(){playFile(e.n+'/','upResult',{shuffle:1});});cp(act,e.n+'/');
        btn(act,'\u2716','Ordner mit Inhalt l\u00f6schen',function(){if(!confirm('Ordner mit allem Inhalt '+e.n+' l\u00f6schen?'))return;postApi('/api/delete',{file:e.n+'/'},'upResult').then(function(){loadFiles('');});});}
      else{td.textContent=e.n;cell(tr,Math.round(e.s/1024)+' KB');act=cell(tr,null);
        btn(act,'\u25B6','Abspielen (reiht sich in die Warteschlange ein)',function(){playFile(n,'upResult');});dl(act,n);cp(act,n);
        btn(act,'\u270E','Umbenennen',function(){renFile(n);});btn(act,'\u2716','Datei l\u00f6schen',function(){delFile(n);});}
      tb.appendChild(tr);});
    if(!j.entries.length)tb.appendChild(document.createElement('tr')).appendChild(document.createElement('td')).textContent='Keine MP3-Dateien oder Ordner';
    box.appendChild(tb);}).catch(function(){});}
function uploadNow(){var fs=Array.prototype.slice.call(document.getElementById('upFile').files);if(!fs.length){showRes('upResult',{ok:false,error:'Keine Datei gew&auml;hlt'});return;}
  var i=0,okc=0,bad=[];
  function next(){if(i>=fs.length){var inp=document.getElementById('upFile');inp.value='';loadFiles();
      showRes('upResult',bad.length?{ok:false,error:okc+' von '+fs.length+' hochgeladen; Fehler: '+bad.join(', ')}:{ok:true,msg:okc+(okc==1?' Datei':' Dateien')+' hochgeladen'});return;}
    var f=fs[i],fn=f.name.replace(/[<>&"']/g,'_');showRes('upResult',{ok:true,msg:'Lade hoch ('+(i+1)+'/'+fs.length+'): '+fn+' &hellip;'});
    var fd=new FormData();fd.append('file',f,f.name);
    fetch('/upload',{method:'POST',body:fd}).then(function(r){return r.json();}).then(function(j){if(j&&j.ok)okc++;else bad.push(fn+' ('+((j&&j.error)||'Fehler')+')');})
      .catch(function(){bad.push(fn);}).then(function(){i++;next();});}
  next();}
var nbs={on:false,jump:true,name:'',pm:0,rate:0,dur:0,t0:0};
function mmss(x){x=Math.round(x);return Math.floor(x/60)+':'+('0'+x%60).slice(-2);}
function barTick(){var pm=nbs.on?Math.min(1000,nbs.pm+nbs.rate*(Date.now()-nbs.t0)/1000):0;
  document.querySelectorAll('.nowbar').forEach(function(bar){var f=bar.firstChild;f.style.transition=nbs.jump?'none':'width .25s linear';f.style.width=(pm/10)+'%';
    bar.title=nbs.on&&nbs.dur>0?mmss(pm/1000*nbs.dur)+' / '+mmss(nbs.dur):'';});nbs.jump=false;}
setInterval(barTick,250);
var SAVEN=0;try{SAVEN=+sessionStorage.getItem('saveN')||0;}catch(e){}
function saveBannerShow(t,n){var b=document.getElementById('saveBanner');if(!b||!t||!n||n<=SAVEN)return;document.getElementById('saveBannerText').textContent=t;b.style.display='block';b.setAttribute('data-n',n);}
function saveBannerClose(){var b=document.getElementById('saveBanner');if(!b)return;SAVEN=+b.getAttribute('data-n')||SAVEN;try{sessionStorage.setItem('saveN',String(SAVEN));}catch(e){}b.style.display='none';}
var SPSRC={voicerss:'VoiceRSS',sd:'gespeichert auf SD-Karte',flash:'gespeichert im Flash',cache:'Zwischenspeicher'},SAYSEQ=0;
function pollPlay(){if(document.hidden)return;fetch('/api/status',{cache:'no-store'}).then(function(r){return r.json();}).then(function(j){
  if(j.muted!==undefined)muteShow(!!j.muted);
  saveBannerShow(j.saveErr,j.saveErrN);
  if(j.speechSeq!==undefined)SAYSEQ=j.speechSeq;
  window.NOWURL=(j.source==='radio'&&j.state==='playing')?(j.url||''):'';if(window.favMarkNow)favMarkNow();
  var el=document.getElementById('playState');if(el)el.textContent='Zustand: '+j.state+(j.error?' ('+j.error+')':'');
  var vs=document.querySelector('.volrange'),ae=document.activeElement;if(vs&&!(ae&&ae.className==='volrange')&&j.volume!==undefined&&+vs.value!==j.volume){volShow(j.volume);}
  {var t='';
    if(j.source==='radio'){t='\u266a Webradio: '+(j.name||j.url)+(j.title?' \u2013 '+j.title:'');}
    else if(j.source==='file'){t='\u266a Datei: '+j.name;}
    else if(j.source==='speech'){t='\u266a Ansage';}
    if(j.speechOn||j.source==='speech'){t='\u266a Ansage'+(SPSRC[j.speechSrc]?' ('+SPSRC[j.speechSrc]+')':'');}
    document.querySelectorAll('.nowplaying').forEach(function(np){np.textContent=t;np.title=j.url||'';
      var row=np.parentNode,bar=row.nextSibling&&row.nextSibling.className==='nowbar'?row.nextSibling:null;
      if(!bar){bar=document.createElement('div');bar.className='nowbar';bar.style.cssText='height:6px;margin:2px auto 8px;max-width:100%;background:#3a4147;border-radius:3px;overflow:hidden';bar.innerHTML='<div style="height:100%;width:0;background:var(--ok)"></div>';row.parentNode.insertBefore(bar,row.nextSibling);}
      var card=row.parentNode.querySelector('.card');if(card&&card.offsetWidth)bar.style.width=card.offsetWidth+'px';
      bar.style.display=j.source==='radio'?'none':'';});
    var on=j.source==='file'&&j.pm!==undefined;
    nbs={on:on,jump:!on||nbs.name!==j.name||j.pm<nbs.pm-50,name:j.name,pm:on?j.pm:0,rate:on?(+j.rate||0):0,dur:on?(+j.dur||0):0,t0:Date.now()};
    barTick();
    var ib=document.getElementById('radioInfoBox');
    if(ib){var tb=document.getElementById('radioInfo'),rows=[];
      if(j.source==='radio'){rows=[['Sender',j.name],['Titel',j.title],['Genre',j.genre],['Beschreibung',j.desc],['Webseite',j.web,1],['Logo',j.logo,1],['Bitrate',j.bitrate?(j.bitrate>=1000?Math.round(j.bitrate/1000):j.bitrate)+' kbit/s':''],['Server',j.host],['Codec',j.codec],['Abtastrate',j.rate?j.rate+' Hz':''],['Kan\u00e4le',j.ch],['Bits',j.bits]].filter(function(r){return r[1];});}
      ib.style.display=rows.length?'':'none';
      var key=JSON.stringify(rows);
      if(tb.getAttribute('data-k')!==key){tb.setAttribute('data-k',key);tb.textContent='';
        rows.forEach(function(r){var tr=document.createElement('tr'),a=document.createElement('td'),b=document.createElement('td');a.style.cssText='color:var(--muted);width:30%;vertical-align:top;word-break:break-all';a.textContent=r[0];
          b.style.wordBreak='break-all';
          if(r[2]&&/^https?:\/\//i.test(r[1])){var l=document.createElement('a');l.href=r[1];l.target='_blank';l.rel='noopener noreferrer';l.textContent=r[1];b.appendChild(l);}else b.textContent=r[1];
          tr.appendChild(a);tr.appendChild(b);tb.appendChild(tr);});}}
    document.querySelectorAll('.stationrow').forEach(function(r){var on=j.source==='radio'&&j.url&&r.getAttribute('data-url')===j.url;var n=r.firstChild;n.style.color=on?'var(--ok)':'var(--muted)';n.style.fontWeight=on?'bold':'normal';var b=r.querySelector('.playbtn');if(b&&r.getAttribute('data-url')){var num=r.getAttribute('data-n');
      if(on){b.innerHTML='&#9632;';b.title='Stopp';b.onclick=function(){stopNow();};}
      else{b.innerHTML='&#9654;';b.title='Abspielen';b.onclick=function(){playStation(num);};}}});
    document.querySelectorAll('.stopbtn').forEach(function(sb){sb.disabled=(j.state==='idle');});}}).catch(function(){});}
function wifiFill(list){
  for(var i=1;i<=3;i++){var s=document.getElementById('ssid_select'+i),t=document.getElementById('ssid'+i);if(!s||!t)continue;
    s.innerHTML='';var o0=document.createElement('option');o0.value='';o0.textContent='Netzwerk auswählen';s.appendChild(o0);
    list.forEach(function(n){var o=document.createElement('option');o.value=n.ssid;o.textContent=n.ssid+' ('+n.rssi+' dBm, '+(n.enc===0?'Offen':'Gesichert')+')';if(n.ssid===t.value)o.selected=true;s.appendChild(o);});}}
function wifiSelText(txt){for(var i=1;i<=3;i++){var s=document.getElementById('ssid_select'+i);if(s)s.innerHTML='<option>'+txt+'</option>';}}
function scanWifi(tries){tries=tries||0;if(!document.getElementById('ssid_select1'))return;wifiSelText('WLAN-Scan läuft …');
  fetch('/api/scanwifi',{cache:'no-store'}).then(function(r){return r.json();}).then(function(list){
    if(!list.length&&tries<6){setTimeout(function(){scanWifi(tries+1);},3000);return;}wifiFill(list);}).catch(function(){wifiSelText('Scan fehlgeschlagen');});}
function rescanWifi(){var b=document.getElementById('rescanBtn');if(!b)return;b.disabled=true;
  var h=document.createElement('div');h.className='flash';h.textContent='Suche nach WLAN-Netzen – die Seite lädt in 10 Sekunden neu';b.parentNode.parentNode.insertBefore(h,b.parentNode);
  fetch('/api/rescanwifi',{method:'POST'}).catch(function(){}).finally(function(){setTimeout(function(){location.href=location.pathname+'?tab=wlan';},10000);});}
function grpGrow(n){var v=document.getElementById('mq_g'+n).value.trim(),r=document.getElementById('grpRow'+(n+1));if(v&&r)r.style.display='';}
function ntpGrow(n){var v=document.getElementById('ntpServerInput'+n).value.trim(),r=document.getElementById('ntpRow'+(n+1));if(v&&r)r.style.display='';}
function testNtp(n){var box=document.getElementById('ntpTestResult'+n);var v=document.getElementById('ntpServerInput'+n).value;
  box.innerHTML='';
  fetch('/api/testNtp?server='+encodeURIComponent(v)).then(function(r){return r.text();}).then(function(t){
    if(t.indexOf('OK|')===0){box.className='res-ok';box.innerHTML='&#10004; '+t.substring(3);}
    else{box.className='res-bad';box.innerHTML='&#10008; Server nicht erreichbar';}
  }).catch(function(){box.className='res-bad';box.innerHTML='&#10008; Server nicht erreichbar';});}
var TABINIT={};
TABINIT.ansage=function(){fillVoiceSel('sayVoice',document.getElementById('sayLang').value,true);};
TABINIT.audio=function(){fillVoiceSel('cfgVoice',(document.getElementById('cfgLang')||{}).value,true);ttsInfo();};
TABINIT.radio=function(){rbInit();listIndex();favLoad();};
TABINIT.mp3=function(){loadFiles();};
TABINIT.sd=function(){sdLoad('/');};
TABINIT.pins=function(){checkPins();if(window.pinsInit)pinsInit();};
TABINIT.wlan=function(){if(location.search.indexOf('tab=wlan')>=0)scanWifi();};
TABINIT.status=function(){if(window.langList)langList();};
TABINIT.sicherung=function(){bkFilesInfo();};
TABINIT.log=function(){if(window.logInit)logInit();};
function tabInit(k,p){p.querySelectorAll('.codehost').forEach(function(c){c.textContent=c.textContent.replace(/@HOST@/g,location.host);});if(TABINIT[k])TABINIT[k]();pollPlay();}
// Beim Oeffnen von MP3 (Flash) und SD-Karte die Liste immer neu laden (ein erst jetzt geladener Tab holt sie selbst).
// When opening MP3 (Flash) and SD card always reload the list (a tab that is only loaded now fetches it itself).
function tabShow(k){var p=document.querySelector('.panel-'+k);if(!p||p.getAttribute('data-lazy')!==null)return;if(k==='mp3')loadFiles(fsCur);else if(k==='sd')sdLoad(sdCur);}
function tabLoad(k){var p=document.querySelector('.panel-'+k);if(!p||p.getAttribute('data-lazy')!=='1')return;p.setAttribute('data-lazy','0');
  p.innerHTML='<div class="card"><p>Lade \u2026</p></div>';
  fetch('/panel?tab='+k,{cache:'no-store'}).then(function(r){if(!r.ok)throw new Error('http');return r.text();}).then(function(t){p.innerHTML=t;p.removeAttribute('data-lazy');tabInit(k,p);})
    .catch(function(){p.setAttribute('data-lazy','1');p.innerHTML='<div class="card"><p>Tab konnte nicht geladen werden.</p><button type="button" onclick="tabLoad(\''+k+'\')" style="width:auto;padding:8px 14px">Erneut versuchen</button></div>';});}
(function(){
  function tabUrl(k){try{history.replaceState(null,'','?tab='+k);}catch(e){}}
  document.querySelectorAll('.tabctrl').forEach(function(r){r.addEventListener('change',function(){if(r.checked){var k=r.id.replace('tab-','');tabLoad(k);tabUrl(k);tabShow(k);}});});
  var ap=document.querySelector('.panel-'+ACT_TAB);if(ap)tabInit(ACT_TAB,ap);
  var cr=document.querySelector('.tabctrl:checked');if(cr){var ck=cr.id.replace('tab-','');tabLoad(ck);tabUrl(ck);}
  setInterval(pollPlay,3000);})();
window.logInit=function(){
  var cb=document.getElementById('logAutoRefresh');var pre=document.getElementById('logContent');
  var errEl=document.getElementById('logErrorHint');var btn=document.getElementById('logRefreshNow');var timer=null;
  var stored=null;try{stored=localStorage.getItem('netspeakerLogAutoRefresh');}catch(e){}
  cb.checked=(stored==='1');
  function refreshLog(){fetch('/log',{cache:'no-store'}).then(function(r){return r.text();}).then(function(t){
    errEl.classList.remove('show');pre.textContent=t||'(leer)';pre.scrollTop=pre.scrollHeight;}).catch(function(){errEl.classList.add('show');});}
  function stopTimer(){if(timer){clearInterval(timer);timer=null;}}
  function applyState(){stopTimer();if(cb.checked&&!document.hidden){timer=setInterval(refreshLog,10000);}}
  btn.addEventListener('click',refreshLog);
  cb.addEventListener('change',function(){try{localStorage.setItem('netspeakerLogAutoRefresh',cb.checked?'1':'0');}catch(e){}if(cb.checked)refreshLog();applyState();});
  document.addEventListener('visibilitychange',function(){if(document.hidden){stopTimer();}else{if(cb.checked)refreshLog();applyState();}});
  refreshLog();applyState();
};
)js";

String flashText(const String& code) {
    if (code == "saved") return "Gespeichert";
    if (code == "pinserr") return "Pins nicht gespeichert: ein Pin ist doppelt vergeben oder nicht erlaubt (alles andere wurde gespeichert)";
    if (code == "restart") return "Gespeichert - Neustart n&ouml;tig (Hostname oder Pins)";
    if (code == "hostbad") return "Hostname ung&uuml;ltig (erlaubt: a-z, 0-9, Bindestrich)";
    if (code == "wifideleted") return "Netzwerk gel&ouml;scht";
    if (code == "wifiswitch") return "Verbinde mit dem gew&auml;hlten Netz - das Ger&auml;t startet neu";
    if (code == "wifiprivate") return "Nur aus dem lokalen Netz m&ouml;glich";
    return "";
}


// Favoritenliste: eigene Liste, unabhaengig von der Senderliste; Sender kommen mit dem Knopf + aus der Senderliste hinein und stehen nach dem Laden einer Liste vorn.
// Favorites list: a list of its own, independent of the station list; stations get in with the + button of the station list and are at the front after a list is loaded.

#define FAV_SLOTS 40

String favName[FAV_SLOTS];
String favUrl[FAV_SLOTS];
bool favLoaded = false;
bool favMqttPending = false;   // Favoriten wurden geaendert und muessen per MQTT gemeldet werden / favorites changed and must be reported via MQTT

// Die Favoriten liegen in einer Datei im Dateisystem (eine Zeile je Favorit: Name, Tab, URL), nicht im knappen NVS-Speicher der Einstellungen.
// The favorites live in a file in the file system (one line per favorite: name, tab, URL), not in the scarce NVS memory of the settings.

#define FAV_FILE "/favorites.dat"

void favSaveAll() {
    favMqttPending = true;
    if (!fsReady) return;
    File f = LittleFS.open(FAV_FILE, FILE_WRITE);
    if (!f) {
        logLine("[FAV] cannot write " FAV_FILE);
        return;
    }
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (favUrl[i].isEmpty()) continue;
        String nm = favName[i];
        nm.replace("\t", " ");
        nm.replace("\r", " ");
        nm.replace("\n", " ");
        f.print(nm);
        f.print("\t");
        f.print(favUrl[i]);
        f.print("\n");
    }
    f.close();
}

// Beim ersten Zugriff laden; fehlt die Datei, werden Favoriten einer aelteren Firmware aus dem NVS uebernommen und dort geloescht.
// Loaded on first access; if the file is missing, favorites of an older firmware are taken over from the NVS and deleted there.

void favEnsure() {
    if (favLoaded) return;
    favLoaded = true;
    if (!fsReady) return;
    if (LittleFS.exists(FAV_FILE)) {
        File f = LittleFS.open(FAV_FILE, FILE_READ);
        int n = 0;
        while (f && f.available() && n < FAV_SLOTS) {
            String ln = f.readStringUntil('\n');
            ln.replace("\r", "");
            int t = ln.indexOf('\t');
            if (t < 0 || t + 1 >= (int)ln.length()) continue;
            favName[n] = ln.substring(0, t);
            favUrl[n] = ln.substring(t + 1);
            n++;
        }
        if (f) f.close();
        return;
    }
    int n = 0;
    for (int i = 0; i < FAV_SLOTS; i++) {
        String nm = prefs.getString(("fn" + String(i + 1)).c_str(), "");
        String u = prefs.getString(("fu" + String(i + 1)).c_str(), "");
        prefs.remove(("fn" + String(i + 1)).c_str());
        prefs.remove(("fu" + String(i + 1)).c_str());
        if (u.isEmpty()) continue;
        favName[n] = nm;
        favUrl[n] = u;
        n++;
    }
    favSaveAll();
}

// Veroeffentlicht die Favoriten (retained) unter <Basis>/favorites; beim Verbinden und nach jeder Aenderung der Liste.
// Publishes the favorites (retained) under <base>/favorites; when connecting and after every change of the list.

void publishFavorites(bool force) {
    if (!mqttClient.connected()) return;
    if (!force && !favMqttPending) return;
    favEnsure();
    favMqttPending = false;
    String j = "{\"max\":" + String(FAV_SLOTS) + ",\"favorites\":[";
    bool first = true;
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (favUrl[i].isEmpty()) continue;
        if (!first) j += ",";
        first = false;
        j += "{\"n\":" + String(i + 1) + ",\"name\":\"" + jsonEscape(favName[i]) + "\",\"url\":\"" + jsonEscape(favUrl[i]) + "\"}";
    }
    j += "]}";
    if (!mqttClient.publish((mqttBaseTopic() + "/favorites").c_str(), j.c_str(), true)) logLine("[MQTT] favorites not published (too large for the buffer?)");
}

void sendChunk(const String& s) {
    webserver.sendContent(s);
    audioPump();
}

// Lange Antworten (Log, Export, Listen) in 1-KB-Stuecken senden und dazwischen den Audio-Puffer nachladen: ein einziges send() haelt die
// Hauptschleife an, bis der Client alles abgeholt hat (bis zu mehreren Sekunden, hoerbar als slow stream).
// Send long responses (log, export, lists) in 1 KB pieces and refill the audio buffer in between: a single send() holds the main loop
// until the client has taken everything (up to several seconds, audible as slow stream).

void sendPumped(int code, const char* type, const String& s) {
    if (s.length() <= 1400) {
        webserver.send(code, type, s);
        return;
    }
    webserver.setContentLength(CONTENT_LENGTH_UNKNOWN);
    webserver.send(code, type, "");
    const char* p = s.c_str();
    size_t left = s.length();
    while (left > 0) {
        size_t n = left > 1024 ? 1024 : left;
        webserver.sendContent(p, n);
        p += n;
        left -= n;
        audioPump();
    }
    webserver.sendContent("");
}

// Sendet den Inhalt eines Tabs (ohne den Rahmen <div class='tabpanel'>); die Doku-Seite schiebt das Verkabelungsbild direkt aus dem Flash ein.
// Sends the content of one tab (without the <div class='tabpanel'> frame); the docs page inserts the wiring picture straight from flash.

void sendPanelBody(const String& k) {
    if (k == "ansage") sendChunk(panelSpeak());
    else if (k == "radio") sendChunk(panelRadio());
    else if (k == "sd") sendChunk(panelSd());
    else if (k == "mp3") sendChunk(panelMp3());
    else if (k == "pins") sendChunk(panelPins());
    else if (k == "audio") sendChunk(panelAudio());
    else if (k == "mqtt") sendChunk(panelMqtt());
    else if (k == "wlan") sendChunk(panelWlan());
    else if (k == "zeit") sendChunk(panelTime());
    else if (k == "status") sendChunk(panelStatus());
    else if (k == "log") sendChunk(panelLog());
    else if (k == "sicherung") sendChunk(panelBackup());
    else if (k == "doku") {
        String doc = panelDoc();
        int wv = doc.indexOf("<!--WIRING_VIEW-->");
        if (wv < 0) {
            sendChunk(doc);
            return;
        }
        sendChunk(doc.substring(0, wv));
        doc.remove(0, wv + 18);
        sendChunk("<div class='card doc' style='max-width:1200px'><h3>Verkabelung (Ansicht)</h3><p>Dieselben Anschl&uuml;sse als Ansicht mit den Bauteilen: Verst&auml;rker und Lautsprecher links, SD-Kartenleser rechts vom Waveshare ESP32-S3-Zero. Das Bild zeigt die Standard-Pins; die Pins im Tab Audio sind &auml;nderbar (das Schaltbild oben passt sich an).</p><div style='background:#fff;border-radius:8px;padding:6px;overflow-x:auto'>");
        const char* sv = WIRING_VIEW_SVG;
        size_t left = strlen(sv);
        while (left > 0) {
            size_t n = left > 1024 ? 1024 : left;
            webserver.sendContent(sv, n);
            sv += n;
            left -= n;
            audioPump();
        }
        sendChunk("</div></div>");
        sendChunk(doc);
    }
}

// Die frueheren Tabnamen bleiben als Adresse gueltig (Lesezeichen): sprechen heisst jetzt ansage.
// The former tab names stay valid as an address (bookmarks): sprechen is now called ansage.

void tabKeyNorm(String& k) {
    if (k == "sprechen") k = "ansage";
}

bool tabKeyValid(const String& k) {
    for (int i = 0; i < TAB_COUNT; i++) {
        if (k == TAB_KEYS[i]) return true;
    }
    return false;
}

// Liefert einen einzelnen Tab zum Nachladen: /panel?tab=audio.
// Delivers a single tab for lazy loading: /panel?tab=audio.

void handlePanel() {
    String k = webserver.arg("tab");
    tabKeyNorm(k);
    if (!tabKeyValid(k)) {
        webserver.send(400, "text/plain; charset=utf-8", "Unknown tab");
        return;
    }
    webserver.setContentLength(CONTENT_LENGTH_UNKNOWN);
    webserver.sendHeader("Cache-Control", "no-store");
    webserver.send(200, "text/html; charset=utf-8", "");
    sendPanelBody(k);
    webserver.sendContent("");
}

void handleRoot() {
    String act = webserver.arg("tab");
    tabKeyNorm(act);
    if (!tabKeyValid(act)) act = TAB_KEYS[0];
    webserver.setContentLength(CONTENT_LENGTH_UNKNOWN);
    webserver.sendHeader("Cache-Control", "no-store");
    webserver.send(200, "text/html; charset=utf-8", "");
    sendChunk("<!DOCTYPE html><html lang='de'><head><meta charset='utf-8'><meta name='viewport' content='width=device-width,initial-scale=1'><title>" PROJECT_TITLE "</title><style>");
    sendChunk(FPSTR(PAGE_CSS));
    String tabCss;
    for (int i = 0; i < TAB_COUNT; i++) {
        tabCss += String("#tab-") + TAB_KEYS[i] + ":checked ~ .tabnav label[for='tab-" + TAB_KEYS[i] + "']{background:var(--accent);color:#1a1200;border-color:var(--accent);}";
        tabCss += String("#tab-") + TAB_KEYS[i] + ":checked ~ .panel-" + TAB_KEYS[i] + "{display:block;}";
    }
    sendChunk(tabCss + "</style></head><body>");
    sendChunk(topbarHtml());
    sendChunk("<noscript><p>Diese Seite braucht JavaScript.</p></noscript><div class='page'><div class='flash bad' id='saveBanner' style='display:none'><span id='saveBannerText'></span> <button type='button' onclick='saveBannerClose()' style='width:auto;padding:2px 8px;margin-left:8px'>&#10006;</button></div>");
    String msg = flashText(webserver.arg("msg"));
    if (msg.length() > 0) {
        sendChunk("<div class='flash' id='flashBox'>" + msg + "</div><script>setTimeout(function(){var b=document.getElementById('flashBox');if(b)b.style.display='none';},4000);</script>");
    }

    // Die Tab-Eingaben, .tabnav und alle .tabpanel muessen direkte Geschwister bleiben (CSS-Selektor :checked ~).
    // The tab inputs, .tabnav and all .tabpanel must stay direct siblings (CSS selector :checked ~).

    String tabs;
    for (int i = 0; i < TAB_COUNT; i++) {
        tabs += String("<input type='radio' name='tabs' id='tab-") + TAB_KEYS[i] + "' class='tabctrl'" + (act == TAB_KEYS[i] ? " checked" : "") + ">";
    }
    tabs += "<div class='tabnav'>";
    for (int i = 0; i < TAB_COUNT; i++) {
        tabs += String("<label for='tab-") + TAB_KEYS[i] + "' title='" + TAB_TIPS[i] + "'>" + TAB_LABELS[i] + "</label>";
    }
    tabs += "</div>";
    sendChunk(tabs);
    for (int i = 0; i < TAB_COUNT; i++) {
        bool on = act == TAB_KEYS[i];
        sendChunk(String("<div class='tabpanel panel-") + TAB_KEYS[i] + "'" + (on ? "" : " data-lazy='1'") + ">");
        if (on) sendPanelBody(TAB_KEYS[i]);
        sendChunk("</div>");
    }
    sendChunk("</div>");
    sendChunk("<script>");
    sendChunk("var ACT_TAB='" + act + "';");
    sendChunk("var DEF_LANG='" + jsonEscape(cfg.vlang) + "';");
    sendChunk("var UI_HOST='" + jsonEscape(cfg.host) + "';");
    sendChunk("var MQTT_BASE='" + jsonEscape(mqttBaseTopic()) + "';var MQTT_ON=" + (cfg.mqttServer.isEmpty() ? "false" : "true") + ";");
    sendChunk(FPSTR(TOPBAR_JS));
    sendChunk(FPSTR(PAGE_JS));
    sendChunk(FPSTR(PINS_JS));
    sendChunk(FPSTR(LANG_JS));
    sendChunk("</script></body></html>");
    webserver.sendContent("");
}

// ---------------------------------------------------------------------------
// Speichern, Export, Import / save, export, import

void redirectTab(const char* tab, const char* msg) {
    webserver.sendHeader("Location", String("/?tab=") + tab + "&msg=" + msg);
    webserver.send(303);
}

// Entfernt Luecken in der Liste der gespeicherten Plaetze: belegte Plaetze ruecken nach oben, alles wird neu gespeichert.
// Removes gaps in the list of stored slots: used slots move up, everything is stored again.

void compactStations() {
    int dst = 0;
    for (int i = 0; i < RADIO_SLOTS; i++) {
        if (cfg.radioUrl[i].isEmpty()) continue;
        if (dst != i) {
            cfg.radioName[dst] = cfg.radioName[i];
            cfg.radioUrl[dst] = cfg.radioUrl[i];
            cfg.radioVol[dst] = cfg.radioVol[i];
        }
        dst++;
    }
    for (int i = dst; i < RADIO_SLOTS; i++) {
        cfg.radioName[i] = "";
        cfg.radioUrl[i] = "";
        cfg.radioVol[i] = -1;
    }
    for (int i = 0; i < RADIO_SLOTS; i++) {
        String n = String(i + 1);
        prefs.putString(("rn" + n).c_str(), cfg.radioName[i]);
        prefs.putString(("ru" + n).c_str(), cfg.radioUrl[i]);
        prefs.putInt(("rv" + n).c_str(), cfg.radioVol[i]);
    }
    publishStations();
}

void handleSave() {
    String sect = webserver.arg("sect");
    bool restart = false;
    bool pinsBad = false;
    if (sect == "wlan") {
        if (webserver.hasArg("host")) {
            String host = cleanHost(webserver.arg("host"));
            if (host != cfg.host) restart = true;
            cfg.host = host;
            prefs.putString("host", host);
        }

        // Nur Plaetze, die im Formular standen (belegte plus ein leerer), werden gelesen; danach rueckt alles ohne Luecken nach oben.
        // Only slots that were in the form (used plus one empty) are read; afterwards everything moves up without gaps.

        String ns[3], np[3];
        for (int i = 0; i < 3; i++) {
            String n = String(i + 1);
            ns[i] = cfg.ssid[i];
            np[i] = cfg.pass[i];
            if (!webserver.hasArg("ssid" + n)) continue;
            String ssid = webserver.arg("ssid" + n);
            ssid.trim();
            String pass = webserver.arg("pass" + n);

            // Leeres Passwortfeld behaelt das gespeicherte Passwort derselben SSID.
            // An empty password field keeps the stored password of the same SSID.

            if (pass.isEmpty() && ssid == cfg.ssid[i]) pass = cfg.pass[i];
            if (ssid.isEmpty()) pass = "";
            ns[i] = ssid;
            np[i] = pass;
        }
        int dst = 0;
        for (int i = 0; i < 3; i++) {
            if (ns[i].isEmpty()) continue;
            if (dst != i) {
                ns[dst] = ns[i];
                np[dst] = np[i];
            }
            dst++;
        }
        for (int i = dst; i < 3; i++) {
            ns[i] = "";
            np[i] = "";
        }
        for (int i = 0; i < 3; i++) {
            cfg.ssid[i] = ns[i];
            cfg.pass[i] = np[i];
            prefs.putString(("ssid" + String(i + 1)).c_str(), ns[i]);
            prefs.putString(("pass" + String(i + 1)).c_str(), np[i]);
        }
        wifiRetryNow();
    } else if (sect == "voice") {
        String key = webserver.arg("vkey");
        key.trim();
        cfg.vkey = key;
        prefs.putString("vkey", key);
        cfg.vlang = webserver.arg("vlang");
        cfg.vvoice = webserver.arg("vvoice");
        cfg.vvoice.trim();
        cfg.vfmt = webserver.arg("vfmt");
        cfg.vrate = constrain(webserver.arg("vrate").toInt(), -10, 10);
        prefs.putString("vlang", cfg.vlang);
        prefs.putString("vvoice", cfg.vvoice);
        prefs.putString("vfmt", cfg.vfmt);
        prefs.putInt("vrate", cfg.vrate);
    } else if (sect == "audio") {
        // Alle sieben Pins (Verstaerker und SD-Karte) werden zusammen geprueft: erlaubt und paarweise verschieden, sonst bleibt alles beim Alten.
        // All seven pins (amplifier and SD card) are checked together: allowed and pairwise different, otherwise everything stays as it was.

        int* pinTargets[7] = {&cfg.din, &cfg.bclk, &cfg.lrc, &cfg.sdCs, &cfg.sdSck, &cfg.sdMosi, &cfg.sdMiso};
        const char* pinKeys[7] = {"din", "bclk", "lrc", "sdcs", "sdsck", "sdmosi", "sdmiso"};
        int pinNew[7];
        bool pinsOk = true;
        for (int i = 0; i < 7; i++) {
            pinNew[i] = webserver.arg(pinKeys[i]).toInt();
            if (!pinAllowed(pinNew[i])) pinsOk = false;
            for (int j = 0; j < i; j++) {
                if (pinNew[i] == pinNew[j]) pinsOk = false;
            }
        }
        pinsBad = !pinsOk;
        bool sdOldOn = cfg.sdOn;
        int sdOld[4] = {cfg.sdCs, cfg.sdSck, cfg.sdMosi, cfg.sdMiso};
        if (pinsOk) {
            for (int i = 0; i < 7; i++) {
                if (pinNew[i] == *pinTargets[i]) continue;
                if (i < 3) restart = true;
                *pinTargets[i] = pinNew[i];
                prefs.putInt(pinKeys[i], pinNew[i]);
            }
        }
        int volOld = cfg.vol;
        cfg.vol = constrain(webserver.arg("vol").toInt(), 0, VOLUME_MAX);
        prefs.putInt("vol", cfg.vol);
        if (cfg.vol != volOld) applyVolumeSmooth(cfg.vol);
        cfg.volRampMs = constrain(webserver.arg("vramp").toInt(), 0, VOLUME_RAMP_MAX_MS);
        prefs.putInt("vramp", cfg.volRampMs);
        cfg.fadeMs = constrain(webserver.arg("fade").toInt(), 0, FADE_MAX_MS);
        prefs.putInt("fade", cfg.fadeMs);
        cfg.switchFadeMs = constrain(webserver.arg("swfade").toInt(), 0, FADE_MAX_MS);
        prefs.putInt("swfade", cfg.switchFadeMs);
        cfg.titleMatch = webserver.arg("tmatch");
        cfg.titleMatch.trim();
        cfg.titleVol = constrain(webserver.arg("tvol").toInt(), 0, VOLUME_MAX);
        prefs.putString("tmatch", cfg.titleMatch);
        prefs.putInt("tvol", cfg.titleVol);
        cfg.titleMaxS = constrain(webserver.arg("tmax").toInt(), 0, 3600);
        prefs.putInt("tmax", cfg.titleMaxS);
        cfg.mixAnn = webserver.hasArg("mix");
        cfg.loudNorm = webserver.hasArg("loud");
        prefs.putBool("loud", cfg.loudNorm);
        cfg.radioAgc = webserver.hasArg("agc");
        prefs.putBool("agc", cfg.radioAgc);
        cfg.agcDb = constrain(webserver.arg("agcdb").toInt(), -30, -10);
        prefs.putInt("agcdb", cfg.agcDb);
        cfg.prebufSec = constrain(webserver.arg("prebuf").toInt(), 0, 30);
        prefs.putInt("prebuf", cfg.prebufSec);
        if (audio) audio->setPrebufferSec(cfg.prebufSec);
        agcResetReq = true;
        cfg.duckPct = constrain(webserver.arg("duck").toInt(), 0, 100);
        prefs.putBool("mix", cfg.mixAnn);
        prefs.putInt("duck", cfg.duckPct);
        cfg.sdOn = webserver.hasArg("sdon");
        prefs.putBool("sdon", cfg.sdOn);
        if (sdOldOn != cfg.sdOn || sdOld[0] != cfg.sdCs || sdOld[1] != cfg.sdSck || sdOld[2] != cfg.sdMosi || sdOld[3] != cfg.sdMiso) sdMount();
        cfg.autoStart = webserver.hasArg("autostart");
        cfg.bootTone = webserver.hasArg("btone");
        prefs.putBool("btone", cfg.bootTone);
        prefs.putBool("autostart", cfg.autoStart);
        cfg.resumeLast = webserver.hasArg("resume");
        prefs.putBool("rlast", cfg.resumeLast);
        if (!cfg.resumeLast) saveRadioState("", -1);
        if (webserver.hasArg("vlang")) {
            String key = webserver.arg("vkey");
            key.trim();
            cfg.vkey = key;
            prefs.putString("vkey", key);
            cfg.vlang = webserver.arg("vlang");
            cfg.vvoice = webserver.arg("vvoice");
            cfg.vvoice.trim();
            cfg.vfmt = webserver.arg("vfmt");
            cfg.vrate = constrain(webserver.arg("vrate").toInt(), -10, 10);
            cfg.ttsCache = webserver.hasArg("ttsc");
            prefs.putBool("ttsc", cfg.ttsCache);
            prefs.putString("vlang", cfg.vlang);
            prefs.putString("vvoice", cfg.vvoice);
            prefs.putString("vfmt", cfg.vfmt);
            prefs.putInt("vrate", cfg.vrate);
        }
    } else if (sect == "mqtt") {
        cfg.mqttServer = webserver.arg("mq_srv");
        cfg.mqttServer.trim();
        int port = webserver.arg("mq_port").toInt();
        cfg.mqttPort = (port >= 1 && port <= 65535) ? port : 1883;
        cfg.mqttBase = webserver.arg("mq_base");
        cfg.mqttBase.trim();
        prefs.putString("mq_srv", cfg.mqttServer);
        prefs.putInt("mq_port", cfg.mqttPort);
        prefs.putString("mq_base", cfg.mqttBase);
        String groups[5];
        int gm = 0;
        for (int i = 1; i <= 5; i++) {
            String v = webserver.arg("mq_g" + String(i));
            v.trim();
            if (!v.isEmpty()) groups[gm++] = v;
        }
        for (int i = 0; i < 5; i++) {
            cfg.mqttGroup[i] = i < gm ? groups[i] : String();
            prefs.putString(("mq_g" + String(i + 1)).c_str(), cfg.mqttGroup[i]);
        }
        bool haNew = webserver.hasArg("mq_ha");
        if (cfg.haDisc && !haNew) haRemovePending = true;
        cfg.haDisc = haNew;
        prefs.putBool("mq_ha", haNew);
        cfg.mqttUser = webserver.arg("mq_user");
        cfg.mqttUser.trim();
        if (webserver.arg("mq_pass").length() > 0) cfg.mqttPass = webserver.arg("mq_pass");
        if (cfg.mqttUser.isEmpty()) cfg.mqttPass = "";
        prefs.putString("mq_usr", cfg.mqttUser);
        prefs.putString("mq_pw", cfg.mqttPass);
        mqttReconnectNow();
    } else if (sect == "radio") {
        for (int i = 0; i < RADIO_SLOTS; i++) {
            String n = String(i + 1);
            if (!webserver.hasArg("ru" + n)) continue;
            String name = webserver.arg("rn" + n);
            String url = webserver.arg("ru" + n);
            name.trim();
            url.trim();
            if (name.length() > RADIO_NAME_MAX) name = name.substring(0, RADIO_NAME_MAX);
            if (!(url.startsWith("http://") || url.startsWith("https://")) || url.length() > RADIO_URL_MAX) url = "";
            if (url.isEmpty()) name = "";
            String rv = webserver.arg("rv" + n);
            rv.trim();
            int vol = (rv.isEmpty() || url.isEmpty()) ? -1 : constrain(rv.toInt(), 0, VOLUME_MAX);
            cfg.radioVol[i] = vol;
            prefs.putInt(("rv" + n).c_str(), vol);
            cfg.radioName[i] = name;
            cfg.radioUrl[i] = url;
            prefs.putString(("rn" + n).c_str(), name);
            prefs.putString(("ru" + n).c_str(), url);
        }
        compactStations();
    } else if (sect == "log") {
        cfg.logEnabled = webserver.hasArg("log");
        prefs.putBool("log", cfg.logEnabled);
        cfg.logAutoMin = constrain(webserver.arg("logmin").toInt(), 0, 1440);
        prefs.putInt("logmin", cfg.logAutoMin);
    } else if (sect == "time") {
        String list[5];
        int m = 0;
        for (int i = 1; i <= 5; i++) {
            String v = webserver.arg("ntp" + String(i));
            v.trim();
            if (!v.isEmpty()) list[m++] = v;
        }
        if (m == 0) list[m++] = "pool.ntp.org";
        for (int i = 0; i < 5; i++) {
            cfg.ntp[i] = i < m ? list[i] : String();
            prefs.putString(("ntp" + String(i + 1)).c_str(), cfg.ntp[i]);
        }
        cfg.tz = webserver.arg("tz");
        if (cfg.tz.isEmpty()) cfg.tz = "UTC0";
        prefs.putString("tz", cfg.tz);
        setupTime();
    }
    logLine("[WEB] settings saved: " + sect);
    static const char* const tabForSect[] = {"wlan", "audio", "audio", "mqtt", "zeit", "log", "radio"};
    static const char* const sects[] = {"wlan", "voice", "audio", "mqtt", "time", "log", "radio"};
    const char* tab = "ansage";
    for (int i = 0; i < 7; i++) {
        if (sect == sects[i]) tab = tabForSect[i];
    }
    redirectTab(tab, pinsBad ? "pinserr" : (restart ? "restart" : "saved"));
}

// Favoriten als Text: "favcount=N" gefolgt von favn1/favu1 ...; steht im Export der Einstellungen und in einer eigenen Datei.
// Favorites as text: "favcount=N" followed by favn1/favu1 ...; it is part of the settings export and of a file of its own.

String favExportText() {
    favEnsure();
    int n = 0;
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (!favUrl[i].isEmpty()) n++;
    }
    String t = "favcount=" + String(n) + "\n";
    int k = 0;
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (favUrl[i].isEmpty()) continue;
        k++;
        String nm = favName[i];
        nm.replace("\r", " ");
        nm.replace("\n", " ");
        t += "favn" + String(k) + "=" + nm + "\nfavu" + String(k) + "=" + favUrl[i] + "\n";
    }
    return t;
}

bool favImportLine(const String& k, const String& v) {
    if (k == "favcount") {
        favEnsure();
        for (int i = 0; i < FAV_SLOTS; i++) {
            favName[i] = "";
            favUrl[i] = "";
        }
        return true;
    }
    bool isN = k.startsWith("favn");
    bool isU = k.startsWith("favu");
    if (!isN && !isU) return false;
    int n = k.substring(4).toInt();
    if (n < 1 || n > FAV_SLOTS) return true;
    favEnsure();
    int i = n - 1;
    if (isN) {
        favName[i] = v.substring(0, RADIO_NAME_MAX);
    } else {
        favUrl[i] = ((v.startsWith("http://") || v.startsWith("https://")) && v.length() <= RADIO_URL_MAX) ? v : String();
    }
    return true;
}

void handleFavoritesExport() {
    String t = "# " PROJECT_NAME " favorites\n" + favExportText();
    webserver.sendHeader("Content-Disposition", "attachment; filename=" + cfg.host + "-favorites.txt");
    webserver.sendHeader("Cache-Control", "no-store");
    sendPumped(200, "text/plain; charset=utf-8", t);
}

void handleFavoritesImport() {
    String body = webserver.arg("plain");
    if (body.startsWith("\xEF\xBB\xBF")) body.remove(0, 3);
    if (!body.startsWith("# " PROJECT_NAME " favorites")) {
        webserver.send(200, "text/plain", "FAIL|Das ist keine Favoritendatei dieses Ger\xC3\xA4ts.");
        return;
    }
    int pos = 0;
    while (pos < (int)body.length()) {
        int end = body.indexOf('\n', pos);
        if (end < 0) end = body.length();
        String line = body.substring(pos, end);
        pos = end + 1;
        line.trim();
        int eq = line.indexOf('=');
        if (line.startsWith("#") || eq <= 0) continue;
        favImportLine(line.substring(0, eq), line.substring(eq + 1));
    }
    favEnsure();
    int kk = 0;
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (!favUrl[i].isEmpty()) {
            favName[kk] = favName[i];
            favUrl[kk] = favUrl[i];
            kk++;
        }
    }
    for (int i = kk; i < FAV_SLOTS; i++) {
        favName[i] = "";
        favUrl[i] = "";
    }
    favSaveAll();
    int n = kk;
    logLine("[WEB] favorites loaded: " + String(n));
    webserver.send(200, "text/plain", "OK|" + String(n) + " Favoriten geladen.");
}

bool isPrivateClient();

void handleExport() {
    bool withWifi = flagOn(webserver.arg("wifi")) && isPrivateClient();
    String t = "# " PROJECT_NAME " settings export (";
    t += withWifi ? "with WiFi passwords" : "WiFi passwords omitted";
    t += ", MQTT password and API key omitted)\n";
    t += "host=" + cfg.host + "\n";
    for (int i = 0; i < 3; i++) {
        t += "ssid" + String(i + 1) + "=" + cfg.ssid[i] + "\n";
        if (withWifi) t += "pass" + String(i + 1) + "=" + cfg.pass[i] + "\n";
    }
    for (int i = 0; i < 5; i++) t += "ntp" + String(i + 1) + "=" + cfg.ntp[i] + "\n";
    t += "tz=" + cfg.tz + "\n";
    t += "vlang=" + cfg.vlang + "\nvvoice=" + cfg.vvoice + "\nvfmt=" + cfg.vfmt + "\nvrate=" + String(cfg.vrate) + "\nttsc=" + String(cfg.ttsCache ? 1 : 0) + "\nfxmode=" + String(cfg.fxMode) + "\nfxwet=" + String(cfg.fxWet) + "\neqb=" + String(cfg.eqBass) + "\neqt=" + String(cfg.eqTreble) + "\npanm=" + String(cfg.panMode) + "\npand=" + String(cfg.panDs) + "\n";
    t += "vol=" + String(cfg.vol) + "\nbclk=" + String(cfg.bclk) + "\nlrc=" + String(cfg.lrc) + "\ndin=" + String(cfg.din) + "\n";
    t += "mq_srv=" + cfg.mqttServer + "\nmq_port=" + String(cfg.mqttPort) + "\nmq_user=" + cfg.mqttUser + "\nmq_base=" + cfg.mqttBase + "\n";
    for (int i = 0; i < 5; i++) t += "mq_g" + String(i + 1) + "=" + cfg.mqttGroup[i] + "\n";
    t += "mq_ha=" + String(cfg.haDisc ? 1 : 0) + "\n";
    t += "fade=" + String(cfg.fadeMs) + "\nswfade=" + String(cfg.switchFadeMs) + "\nautostart=" + String(cfg.autoStart ? 1 : 0) + "\nbtone=" + String(cfg.bootTone ? 1 : 0) + "\nresume=" + String(cfg.resumeLast ? 1 : 0) + "\nsdon=" + String(cfg.sdOn ? 1 : 0) + "\nsdcs=" + String(cfg.sdCs) + "\nsdsck=" + String(cfg.sdSck) + "\nsdmosi=" + String(cfg.sdMosi) + "\nsdmiso=" + String(cfg.sdMiso) + "\nvolmax=" + String(VOLUME_MAX) + "\nvramp=" + String(cfg.volRampMs) + "\nmix=" + String(cfg.mixAnn ? 1 : 0) + "\nloud=" + String(cfg.loudNorm ? 1 : 0) + "\nagc=" + String(cfg.radioAgc ? 1 : 0) + "\nagcdb=" + String(cfg.agcDb) + "\nprebuf=" + String(cfg.prebufSec) + "\nduck=" + String(cfg.duckPct) + "\ntmatch=" + cfg.titleMatch + "\ntvol=" + String(cfg.titleVol) + "\ntmax=" + String(cfg.titleMaxS) + "\n";
    t += "log=" + String(cfg.logEnabled ? 1 : 0) + "\nlogmin=" + String(cfg.logAutoMin) + "\n";
    for (int i = 0; i < RADIO_SLOTS; i++) t += "rn" + String(i + 1) + "=" + cfg.radioName[i] + "\nru" + String(i + 1) + "=" + cfg.radioUrl[i] + "\nrv" + String(i + 1) + "=" + (cfg.radioVol[i] >= 0 ? String(cfg.radioVol[i]) : String()) + "\n";
    webserver.sendHeader("Content-Disposition", "attachment; filename=" + cfg.host + "-settings.txt");
    webserver.sendHeader("Cache-Control", "no-store");
    t += favExportText();
    sendPumped(200, "text/plain; charset=utf-8", t);
}

// Importierte Lautstaerken: Dateien ohne volmax=100 stammen von der alten Skala 0 bis 21 und werden umgerechnet.
// Imported volumes: files without volmax=100 come from the old scale 0 to 21 and are converted.

bool importNewScale = true;

int importVol(int x) {
    return importNewScale ? x : (x * VOLUME_MAX + 10) / 21;
}

void handleImport() {
    String body = webserver.arg("plain");
    if (!body.startsWith("# " PROJECT_NAME " settings export")) {
        webserver.send(200, "text/plain", "FAIL|Das ist keine Exportdatei dieses Ger\xC3\xA4ts.");
        return;
    }
    importNewScale = body.indexOf("volmax=100") >= 0;
    int count = 0;
    bool needRestart = false;
    String oldSsid[3] = {cfg.ssid[0], cfg.ssid[1], cfg.ssid[2]};
    String oldPass[3] = {cfg.pass[0], cfg.pass[1], cfg.pass[2]};
    int pos = 0;
    while (pos < (int)body.length()) {
        int end = body.indexOf('\n', pos);
        if (end < 0) end = body.length();
        String line = body.substring(pos, end);
        pos = end + 1;
        line.trim();
        int eq = line.indexOf('=');
        if (line.startsWith("#") || eq <= 0) continue;
        String k = line.substring(0, eq);
        String v = line.substring(eq + 1);
        if (k == "host") {

            // Der Hostname gehoert zum Geraet und wird nicht uebernommen, damit zwei Geraete nie denselben Namen bekommen.
            // The hostname belongs to the device and is not imported, so two devices never get the same name.

            continue;
        } else if (k == "ssid1" || k == "ssid2" || k == "ssid3") {
            int i = k.substring(4).toInt() - 1;
            cfg.ssid[i] = v;

            // Das Passwort bleibt nur, wenn dieselbe SSID schon gespeichert war.
            // The password stays only if the same SSID was already stored.

            cfg.pass[i] = (v == oldSsid[i]) ? oldPass[i] : "";
            prefs.putString(k.c_str(), v);
            prefs.putString(("pass" + String(i + 1)).c_str(), cfg.pass[i]);
        } else if (k == "pass1" || k == "pass2" || k == "pass3") {

            // Passwoerter nur aus dem lokalen Netz; sie stehen in der Sicherung hinter dem Netznamen.
            // Passwords only from the local network; in the backup they follow the network name.

            if (!isPrivateClient()) continue;
            int i = k.substring(4).toInt() - 1;
            cfg.pass[i] = v;
            prefs.putString(k.c_str(), v);
        } else if (k.length() == 4 && k.startsWith("ntp") && k[3] >= '1' && k[3] <= '5') {
            int i = k[3] - '1';
            cfg.ntp[i] = (i == 0 && v.isEmpty()) ? String("pool.ntp.org") : v;
            prefs.putString(k.c_str(), cfg.ntp[i]);
        } else if (k == "tz") { cfg.tz = v.isEmpty() ? "UTC0" : v; prefs.putString("tz", cfg.tz);
        } else if (k == "vlang") { cfg.vlang = v; prefs.putString("vlang", v);
        } else if (k == "vvoice") { cfg.vvoice = v; prefs.putString("vvoice", v);
        } else if (k == "fxmode") { cfg.fxMode = constrain(v.toInt(), 0, 4); prefs.putInt("fxmode", cfg.fxMode); fxApplyCfg();
        } else if (k == "fxwet") { cfg.fxWet = constrain(v.toInt(), 0, 100); prefs.putInt("fxwet", cfg.fxWet); fxApplyCfg();
        } else if (k == "eqb") { cfg.eqBass = constrain(v.toInt(), -12, 12); prefs.putInt("eqb", cfg.eqBass); fxApplyCfg();
        } else if (k == "panm") { cfg.panMode = constrain(v.toInt(), 0, 3); prefs.putInt("panm", cfg.panMode); fxApplyCfg();
        } else if (k == "pand") { cfg.panDs = constrain(v.toInt(), 5, 200); prefs.putInt("pand", cfg.panDs); fxApplyCfg();
        } else if (k == "eqt") { cfg.eqTreble = constrain(v.toInt(), -12, 12); prefs.putInt("eqt", cfg.eqTreble); fxApplyCfg();
        } else if (k == "ttsc") { cfg.ttsCache = v.toInt() != 0; prefs.putBool("ttsc", cfg.ttsCache);
        } else if (k == "vfmt") { cfg.vfmt = v; prefs.putString("vfmt", v);
        } else if (k == "vrate") { cfg.vrate = constrain(v.toInt(), -10, 10); prefs.putInt("vrate", cfg.vrate);
        } else if (k == "vol") { cfg.vol = constrain(importVol(v.toInt()), 0, VOLUME_MAX); prefs.putInt("vol", cfg.vol);
        } else if (k == "bclk" || k == "lrc" || k == "din") {
            int pin = v.toInt();
            if (!pinAllowed(pin)) continue;
            int* target = k == "bclk" ? &cfg.bclk : (k == "lrc" ? &cfg.lrc : &cfg.din);
            if (*target != pin) needRestart = true;
            *target = pin;
            prefs.putInt(k.c_str(), pin);
        } else if (k == "mq_user") { cfg.mqttUser = v; prefs.putString("mq_usr", v);
        } else if (k == "mq_pass") { cfg.mqttPass = v; prefs.putString("mq_pw", v);
        } else if (k == "mq_srv") { cfg.mqttServer = v; prefs.putString("mq_srv", v);
        } else if (k == "mq_port") { int p = v.toInt(); cfg.mqttPort = (p >= 1 && p <= 65535) ? p : 1883; prefs.putInt("mq_port", cfg.mqttPort);
        } else if (k == "mq_base") { cfg.mqttBase = v; prefs.putString("mq_base", v);
        } else if (k == "mq_ha") { bool on = v.toInt() != 0; if (cfg.haDisc && !on) haRemovePending = true; cfg.haDisc = on; prefs.putBool("mq_ha", on);
        } else if (k.length() == 5 && k.startsWith("mq_g") && k[4] >= '1' && k[4] <= '5') { cfg.mqttGroup[k[4] - '1'] = v; prefs.putString(k.c_str(), v);
        } else if (k == "sdon") { cfg.sdOn = v.toInt() != 0; prefs.putBool("sdon", cfg.sdOn);
        } else if (k == "sdcs" || k == "sdsck" || k == "sdmosi" || k == "sdmiso") {
            int pin = v.toInt();
            if (!pinAllowed(pin)) continue;
            int* target = k == "sdcs" ? &cfg.sdCs : (k == "sdsck" ? &cfg.sdSck : (k == "sdmosi" ? &cfg.sdMosi : &cfg.sdMiso));
            if (*target != pin) needRestart = true;
            *target = pin;
            prefs.putInt(k.c_str(), pin);
        } else if (k == "vramp") { cfg.volRampMs = constrain(v.toInt(), 0, VOLUME_RAMP_MAX_MS); prefs.putInt("vramp", cfg.volRampMs);
        } else if (k == "mix") { cfg.mixAnn = v.toInt() != 0; prefs.putBool("mix", cfg.mixAnn);
        } else if (k == "loud") { cfg.loudNorm = v.toInt() != 0; prefs.putBool("loud", cfg.loudNorm);
        } else if (k == "agc") { cfg.radioAgc = v.toInt() != 0; prefs.putBool("agc", cfg.radioAgc);
        } else if (k == "agcdb") { cfg.agcDb = constrain(v.toInt(), -30, -10); prefs.putInt("agcdb", cfg.agcDb);
        } else if (k == "prebuf") { cfg.prebufSec = constrain(v.toInt(), 0, 30); prefs.putInt("prebuf", cfg.prebufSec);
        } else if (favImportLine(k, v)) {
            // Favoriten (favcount, favn1, favu1 ...) sind in favImportLine erledigt.
            // Favorites (favcount, favn1, favu1 ...) are handled in favImportLine.
        } else if (k == "duck") { cfg.duckPct = constrain(v.toInt(), 0, 100); prefs.putInt("duck", cfg.duckPct);
        } else if (k == "tmatch") { cfg.titleMatch = v; prefs.putString("tmatch", v);
        } else if (k == "tmax") { cfg.titleMaxS = constrain(v.toInt(), 0, 3600); prefs.putInt("tmax", cfg.titleMaxS);
        } else if (k == "tvol") { cfg.titleVol = constrain(importVol(v.toInt()), 0, VOLUME_MAX); prefs.putInt("tvol", cfg.titleVol);
        } else if (k == "resume") { cfg.resumeLast = v.toInt() != 0; prefs.putBool("rlast", cfg.resumeLast);
        } else if (k == "btone") { cfg.bootTone = v.toInt() != 0; prefs.putBool("btone", cfg.bootTone);
        } else if (k == "autostart") { cfg.autoStart = v.toInt() != 0; prefs.putBool("autostart", cfg.autoStart);
        } else if (k == "swfade") { cfg.switchFadeMs = constrain(v.toInt(), 0, FADE_MAX_MS); prefs.putInt("swfade", cfg.switchFadeMs);
        } else if (k == "fade") { cfg.fadeMs = constrain(v.toInt(), 0, FADE_MAX_MS); prefs.putInt("fade", cfg.fadeMs);
        } else if (k == "vkey" && v.length() > 0) { cfg.vkey = v; prefs.putString("vkey", v);
        } else if (k == "logmin") { cfg.logAutoMin = constrain(v.toInt(), 0, 1440); prefs.putInt("logmin", cfg.logAutoMin);
        } else if (k == "log") { cfg.logEnabled = v.toInt() != 0; prefs.putBool("log", cfg.logEnabled);
        } else if (k.startsWith("rv") && k.substring(2).toInt() >= 1 && k.substring(2).toInt() <= RADIO_SLOTS) {
            int slot = k.substring(2).toInt() - 1;
            cfg.radioVol[slot] = v.isEmpty() ? -1 : constrain(importVol(v.toInt()), 0, VOLUME_MAX);
            prefs.putInt(k.c_str(), cfg.radioVol[slot]);
        } else if ((k.startsWith("rn") || k.startsWith("ru")) && k.substring(2).toInt() >= 1 && k.substring(2).toInt() <= RADIO_SLOTS) {
            int slot = k.substring(2).toInt() - 1;
            if (k.startsWith("rn")) cfg.radioName[slot] = v.substring(0, RADIO_NAME_MAX);
            else cfg.radioUrl[slot] = ((v.startsWith("http://") || v.startsWith("https://")) && v.length() <= RADIO_URL_MAX) ? v : "";
            prefs.putString(k.c_str(), k.startsWith("rn") ? cfg.radioName[slot] : cfg.radioUrl[slot]);
        } else {
            continue;
        }
        count++;
    }
    if (favLoaded) favSaveAll();
    applyVolume(cfg.vol);
    setupTime();
    mqttReconnectNow();
    wifiRetryNow();
    publishStations();
    logLine("[WEB] settings imported: " + String(count) + " values");
    webserver.send(200, "text/plain", "OK|" + String(count) + " Werte \xC3\xBC" "bernommen." + (needRestart ? " Neustart n\xC3\xB6tig (Hostname oder Pins)." : ""));
}

// ---------------------------------------------------------------------------
// JSON-API / JSON API

void sendJson(int code, const String& json) {
    webserver.sendHeader("Cache-Control", "no-store");
    sendPumped(code, "application/json", json);
}

void sendOk(const String& msg) {
    sendJson(200, "{\"ok\":true,\"msg\":\"" + jsonEscape(msg) + "\"}");
}

void sendErr(int code, const String& msg) {
    sendJson(code, "{\"ok\":false,\"error\":\"" + jsonEscape(msg) + "\"}");
}

// Parameter aus Formular, Query oder einem flachen JSON-Body, zum Beispiel {"text":"Hallo","vol":12}.
// Parameter from form, query or a flat JSON body, for example {"text":"Hallo","vol":12}.

String apiArg(const String& name) {
    if (webserver.hasArg(name)) return webserver.arg(name);
    String body = webserver.arg("plain");
    body.trim();
    if (body.startsWith("{")) return jsonGet(body, name);
    return "";
}

void handleApiSay() {
    String err = commandSay(apiArg("text"), apiArg("lang"), apiArg("voice"), numberOr(apiArg("rate"), 99), numberOr(apiArg("vol"), -1), flagOn(apiArg("save")), apiArg("fx").isEmpty() || flagOn(apiArg("fx")));
    if (err.length() > 0) return sendErr(400, err);
    sendOk("Wird angesagt");
}

void handleApiPlay() {
    String url = apiArg("url");
    String file = apiArg("file");
    int vol = numberOr(apiArg("vol"), -1);
    int pn, pds;
    String panErr = panArgs(apiArg("pan"), apiArg("pansec"), pn, pds);
    String err = url.length() > 0 ? commandPlayUrl(url, vol) : (file.length() > 0 ? (panErr.isEmpty() ? commandPlayFileFx(file, vol, flagOn(apiArg("shuffle")), flagOn(apiArg("loop")), pn, pds) : panErr) : String("url oder file angeben"));
    if (err.length() > 0) return sendErr(400, err);
    sendOk("Wird abgespielt");
}

void handleApiUrl() {
    String err = commandPlayUrl(apiArg("url"), numberOr(apiArg("vol"), -1));
    if (err.length() > 0) return sendErr(400, err);
    sendOk("Wird abgespielt");
}

void handleApiFile() {
    int pn, pds;
    String panErr = panArgs(apiArg("pan"), apiArg("pansec"), pn, pds);
    String err = panErr.isEmpty() ? commandPlayFileFx(apiArg("file"), numberOr(apiArg("vol"), -1), flagOn(apiArg("shuffle")), flagOn(apiArg("loop")), pn, pds) : panErr;
    if (err.length() > 0) return sendErr(400, err);
    sendOk("Wird abgespielt");
}

void handleApiStation() {
    String sel = apiArg("n");
    if (sel.isEmpty()) sel = apiArg("name");
    String err = commandPlayStation(sel, numberOr(apiArg("vol"), -1));
    if (err.length() > 0) return sendErr(400, err);
    sendOk("Wird abgespielt");
}

void handleApiStationDelete() {
    int n = apiArg("n").toInt();
    if (n < 1 || n > RADIO_SLOTS) return sendErr(400, "Platz 1-" + String(RADIO_SLOTS) + " angeben");
    cfg.radioName[n - 1] = "";
    cfg.radioUrl[n - 1] = "";
    prefs.putString(("rn" + String(n)).c_str(), "");
    prefs.putString(("ru" + String(n)).c_str(), "");
    cfg.radioVol[n - 1] = -1;
    compactStations();
    logLine("[WEB] station slot " + String(n) + " deleted, following slots moved up");
    sendOk("Platz " + String(n) + " gel\xC3\xB6scht");
}

// Senderliste als Textdatei sichern und wieder laden; das Laden ersetzt die ganze Liste.
// Save the station list as a text file and load it again; loading replaces the whole list.

void handleStationsExport() {
    String t = "# " PROJECT_NAME " stations\n";
    int n = 0;
    for (int i = 0; i < RADIO_SLOTS; i++) {
        if (cfg.radioUrl[i].isEmpty()) continue;
        n++;
        String nm = cfg.radioName[i];
        nm.replace("\r", " ");
        nm.replace("\n", " ");
        t += "rn" + String(n) + "=" + nm + "\nru" + String(n) + "=" + cfg.radioUrl[i] + "\nrv" + String(n) + "=" + (cfg.radioVol[i] >= 0 ? String(cfg.radioVol[i]) : String()) + "\n";
    }
    webserver.sendHeader("Content-Disposition", "attachment; filename=" + cfg.host + "-stations.txt");
    webserver.sendHeader("Cache-Control", "no-store");
    sendPumped(200, "text/plain; charset=utf-8", t);
}

String stationsApply(String body) {
    if (body.startsWith("\xEF\xBB\xBF")) body.remove(0, 3);
    if (!body.startsWith("# " PROJECT_NAME " stations")) {
        return String("FAIL|Das ist keine Senderliste dieses Ger\xC3\xA4ts.");
    }

    // Erst in Hilfsfelder lesen: eine Datei ohne gueltigen Sender laesst die gespeicherte Liste unberuehrt.
    // Read into helper arrays first: a file without a valid station leaves the stored list untouched.

    String names[RADIO_SLOTS], urls[RADIO_SLOTS];
    int vols[RADIO_SLOTS];
    for (int i = 0; i < RADIO_SLOTS; i++) vols[i] = -1;
    int pos = 0;
    while (pos < (int)body.length()) {
        int e = body.indexOf('\n', pos);
        if (e < 0) e = body.length();
        String line = body.substring(pos, e);
        pos = e + 1;
        line.trim();
        int eq = line.indexOf('=');
        if (eq < 3 || line.startsWith("#")) continue;
        String k = line.substring(0, eq);
        String v = line.substring(eq + 1);
        v.trim();
        int slot = k.substring(2).toInt() - 1;
        if (slot < 0 || slot >= RADIO_SLOTS) continue;
        if (k.startsWith("rn")) names[slot] = v.substring(0, RADIO_NAME_MAX);
        else if (k.startsWith("ru")) urls[slot] = ((v.startsWith("http://") || v.startsWith("https://")) && v.length() <= RADIO_URL_MAX) ? v : "";
        else if (k.startsWith("rv")) vols[slot] = v.isEmpty() ? -1 : constrain(v.toInt(), 0, VOLUME_MAX);
    }
    int count = 0;
    for (int i = 0; i < RADIO_SLOTS; i++) {
        if (!urls[i].isEmpty()) count++;
    }
    if (count == 0) {
        return String("FAIL|Die Datei enth\xC3\xA4lt keinen g\xC3\xBCltigen Sender (URL mit http:// oder https://).");
    }
    // RSA wird nur dann vorn eingetragen, wenn die gespeicherte Senderliste leer ist; bei allen Aenderungen danach wird er nicht wieder eingetragen (in der Liste stehende Plaetze bleiben, wie sie sind).
    // RSA is put at the front only if the stored station list is empty; with all changes after that it is not entered again (entries that are in the list stay as they are).

    bool wasEmpty = true;
    for (int i = 0; i < RADIO_SLOTS; i++) {
        if (!cfg.radioUrl[i].isEmpty()) wasEmpty = false;
    }
    String on[RADIO_SLOTS], ou[RADIO_SLOTS];
    int ov[RADIO_SLOTS];
    int k = 0;
    if (wasEmpty) {
        ou[0] = RSA_URL;
        on[0] = "RSA";
        ov[0] = -1;
        k = 1;
    }

    // Danach die Favoriten, dann die Sender der Liste (ohne Doppelte); bei zu vielen Eintraegen faellt das Ende weg.
    // Then the favorites, then the stations of the list (without duplicates); with too many entries the end is dropped.

    favEnsure();
    for (int f = 0; f < FAV_SLOTS && k < RADIO_SLOTS; f++) {
        if (favUrl[f].isEmpty()) continue;
        bool dup = false;
        for (int j = 0; j < k; j++) {
            if (ou[j] == favUrl[f]) dup = true;
        }
        if (dup) continue;
        on[k] = favName[f];
        ou[k] = favUrl[f];
        ov[k] = -1;
        k++;
    }
    for (int i = 0; i < RADIO_SLOTS; i++) {
        if (urls[i].isEmpty()) continue;
        if (wasEmpty && urls[i] == RSA_URL) {
            on[0] = names[i];
            ov[0] = vols[i];
        } else if (k < RADIO_SLOTS) {
            bool dup = false;
            for (int j = 0; j < k; j++) {
                if (ou[j] == urls[i]) dup = true;
            }
            if (dup) continue;
            on[k] = names[i];
            ou[k] = urls[i];
            ov[k] = vols[i];
            k++;
        }
    }
    count = k;
    for (int i = 0; i < RADIO_SLOTS; i++) {
        bool used = i < k;
        cfg.radioName[i] = used ? on[i] : String();
        cfg.radioUrl[i] = used ? ou[i] : String();
        cfg.radioVol[i] = used ? ov[i] : -1;
    }
    compactStations();
    logLine("[WEB] station list loaded: " + String(count) + " stations");
    return "OK|" + String(count) + " Sender geladen.";
}

void handleStationsImport() {
    webserver.send(200, "text/plain", stationsApply(webserver.arg("plain")));
}

void handleApiStations() {
    sendJson(200, stationsJson());
}

void handleApiStop() {
    commandStop();
    sendOk("Gestoppt");
}

// Stumm schalten: on=1|0 oder toggle=1 (GET oder POST); ohne Angabe wird nur der Zustand gemeldet.
// Mute: on=1|0 or toggle=1 (GET or POST); without a parameter it only reports the state.

void handleApiMute() {
    String a = apiArg("on");
    if (a.isEmpty()) a = apiArg("mute");
    if (flagOn(apiArg("toggle"))) a = "toggle";
    if (!a.isEmpty()) {
        String err = commandMute(a);
        if (err.length() > 0) return sendErr(400, err);
    }
    sendJson(200, String("{\"ok\":true,\"muted\":") + (muted ? "true" : "false") + "}");
}

void handleApiVolume() {
    String v = apiArg("v");

    // Ohne v wird nur gemeldet: volume = allgemeine, playVolume = gerade wirkende Lautstaerke.
    // Without v it only reports: volume = general, playVolume = currently effective volume.

    if (!v.isEmpty()) commandVolume(v.toInt(), numberOr(apiArg("ms"), -1));
    sendJson(200, String("{\"ok\":true,\"volume\":") + String(cfg.vol) + ",\"playVolume\":" + String(currentVolume) + ",\"muted\":" + (muted ? "true" : "false") + "}");
}

// Log ein- oder ausschalten und leeren: enable=1|0, clear=1 (POST); GET liefert den Zustand.
// Switch logging on or off and clear it: enable=1|0, clear=1 (POST); GET returns the state.

void handleApiLog() {
    if (webserver.method() == HTTP_POST) {
        String en = apiArg("enable");
        if (en.length() > 0) {
            cfg.logEnabled = (en == "1" || en == "true");
            prefs.putBool("log", cfg.logEnabled);
        }
        String cl = apiArg("clear");
        if (cl == "1" || cl == "true") clearLogFiles();
    }
    sendJson(200, String("{\"enabled\":") + (cfg.logEnabled ? "true" : "false") + "}");
}
void handleApiStatus() {
    String j = "{\"version\":\"" PROJECT_VERSION "\",\"state\":\"" + playStateName() + "\",\"error\":\"" + jsonEscape(lastError) + "\",\"volume\":" + String(cfg.vol) + ",\"playVolume\":" + String(currentVolume) + ",\"muted\":" + (muted ? "true" : "false") + (ttsSaveErrN > 0 ? ",\"saveErr\":\"" + jsonEscape(ttsSaveErr) + "\",\"saveErrN\":" + String(ttsSaveErrN) : String()) + ",\"queue\":" + String(annCount) + ",\"sd\":\"" + sdState + "\",\"sdMounted\":" + (sdReady ? "true" : "false") + ",\"resume\":" + (resumeUrl.length() > 0 ? "true" : "false");
    bool speechOn = (nowKind == "speech" && playState != PS_IDLE) || (mixT[MIX_ANN].inUse && mixT[MIX_ANN].path == TTS_FILE);
    j += ",\"speechSeq\":" + String(speechSeq) + ",\"speechOn\":" + (speechOn ? "true" : "false");
    if (speechOn) j += ",\"speechSrc\":\"" + speechFrom + "\"";
    bool idleNow = playState == PS_IDLE || nowKind.isEmpty();
    j += ",\"source\":\"" + String(idleNow ? "" : nowKind.c_str()) + "\",\"name\":\"" + jsonEscape(idleNow ? String() : (nowKind == "radio" ? stationDisplayName() : (nowKind == "file" ? nowFile : String()))) + "\",\"title\":\"" + jsonEscape(nowKind == "radio" && !idleNow ? nowTitle : String()) + "\",\"url\":\"" + jsonEscape(nowKind == "radio" && !idleNow ? streamUrl : String()) + "\"";
    if (!idleNow && nowKind == "file" && playState == PS_PLAYING && audio) j += ",\"pos\":" + String(audio->getAudioCurrentTime()) + ",\"dur\":" + String(audio->getAudioFileDuration());
    if (!idleNow && nowKind == "radio") {
        j += ",\"genre\":\"" + jsonEscape(nowGenre) + "\",\"desc\":\"" + jsonEscape(nowDesc) + "\",\"web\":\"" + jsonEscape(nowWeb) + "\",\"logo\":\"" + jsonEscape(nowLogo) + "\",\"host\":\"" + jsonEscape(nowHost) + "\",\"bitrate\":" + String(nowBitrate);
        if (audio && playState == PS_PLAYING) j += ",\"codec\":\"" + jsonEscape(String(audio->getCodecname())) + "\",\"rate\":" + String(audio->getSampleRate()) + ",\"ch\":" + String(audio->getChannels()) + ",\"bits\":" + String(audio->getBitsPerSample());
    }
    if (!idleNow && nowKind == "file" && playState == PS_PLAYING && cfg.loudNorm) j += ",\"gainDb\":" + (fileGainKnown ? String(fileGainCurDb, 1) : String("null"));
    if (agcActive) j += ",\"agcDb\":" + String(agcGainShown, 1);
    if (!idleNow && nowKind == "file" && playState == PS_PLAYING && audio && audio->getFileSize() > 0) {
        uint32_t fsz = audio->getFileSize();
        uint32_t fpos = audio->getAudioFilePosition();
        j += ",\"pm\":" + String((uint32_t)((uint64_t)(fpos > fsz ? fsz : fpos) * 1000ULL / fsz)) + ",\"rate\":" + String((double)audio->getBitRate() / 8.0 * 1000.0 / (double)fsz, 3);
    }
    j += ",\"audioLoopMs\":" + String(diagAudioMs) + ",\"loopMs\":" + String(diagLoopMs) + ",\"bufKb\":" + String(diagBufKb) + ",\"bufMinKb\":" + String(diagBufMinKb) + ",\"decErr\":" + String(diagDecErr);
    j += ",\"nvsUsed\":" + String(nvsUsedEntries()) + ",\"nvsFree\":" + String(nvsFreeEntries());
    j += ",\"uptime\":" + String(millis() / 1000) + ",\"resetReason\":\"" + resetReasonName() + "\",\"wifiReconnects\":" + String(wifiReconnects) + ",\"mqttReconnects\":" + String(mqttReconnects) + ",\"minFreeHeap\":" + String(ESP.getMinFreeHeap()) + ",\"safeMode\":" + (safeMode ? "true" : "false");
    storageRefresh();
    j += ",\"heap\":" + String(ESP.getFreeHeap()) + ",\"fsUsed\":" + String(fsReady ? fsUsedC : 0);
    j += ",\"fsTotal\":" + String(fsReady ? fsTotalC : 0) + "}";
    sendJson(200, j);
}

// Dateiname bereinigen: nur Buchstaben, Ziffern, Punkt, Bindestrich, Unterstrich; erlaubte Endung mp3.
// Clean the file name: only letters, digits, dot, hyphen, underscore; allowed extension mp3.

String cleanFileName(String name) {

    // Der Unterordner ansagen (gespeicherte Texte) bleibt als Vorsatz erhalten, sonst zaehlt nur der Dateiname.
    // The subfolder ansagen (saved texts) stays as a prefix, otherwise only the file name counts.

    String sub;
    if (name.startsWith("ansagen/")) {
        sub = "ansagen/";
        name = name.substring(8);
    }
    int slash = max(name.lastIndexOf('/'), name.lastIndexOf('\\'));
    if (slash >= 0) name = name.substring(slash + 1);
    String out;
    for (size_t i = 0; i < name.length() && out.length() < 120; i++) {
        char c = name[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.' || c == '-' || c == '_') out += c;
        else if (c == ' ') out += '_';
    }
    String lower = out;
    lower.toLowerCase();
    bool okExt = lower.endsWith(".mp3");
    if (!okExt || out.startsWith(".")) return "";
    if (out.length() > 100) out = out.substring(0, 96) + ".mp3";
    return sub + out;
}

// Inhalt eines Ordners der SD-Karte als JSON: mounted, state, size, used (MB), dir und entries (n = Name, d = Ordner, s = Groesse).
// Content of a folder on the SD card as JSON: mounted, state, size, used (MB), dir and entries (n = name, d = folder, s = size).

void handleApiSd() {
    String dir = webserver.arg("dir");
    if (dir.isEmpty()) dir = "/";
    std::vector<SdEntry> list;
    bool ok = sdListDir(dir, list);
    if (!dir.startsWith("/")) dir = "/" + dir;
    String j = String("{\"mounted\":") + (sdReady ? "true" : "false") + ",\"state\":\"" + jsonEscape(sdState) + "\"";
    storageRefresh();
    if (sdReady) j += ",\"size\":" + String((unsigned long)(sdTotalC / 1048576ULL)) + ",\"used\":" + String((unsigned long)(sdUsedC / 1048576ULL));
    j += ",\"dir\":\"" + jsonEscape(dir) + "\",\"ok\":" + (ok ? "true" : "false") + ",\"entries\":[";
    for (size_t i = 0; i < list.size(); i++) {
        if (i) j += ",";
        j += "{\"n\":\"" + jsonEscape(list[i].name) + "\",\"d\":" + (list[i].dir ? "1" : "0") + ",\"s\":" + String((unsigned long)list[i].size) + "}";
    }
    sendJson(200, j + "]}");
}

void handleApiTtsCache() {
    uint32_t bytes = 0;
    int n;
    if (webserver.method() == HTTP_POST && apiArg("clear") == "1") {
        if (!sdReady) return sendErr(400, "SD-Karte nicht verf\xC3\xBCgbar");
        n = ttsCacheInfo(bytes, true);
        return sendOk(String(n) + " Dateien gel\xC3\xB6scht");
    }
    n = ttsCacheInfo(bytes, false);
    sendJson(200, "{\"enabled\":" + String(cfg.ttsCache ? "true" : "false") + ",\"sd\":" + String(sdReady ? "true" : "false") + ",\"files\":" + String(n) + ",\"bytes\":" + String((unsigned long)bytes) + "}");
}

// Klangeffekte lesen und setzen: mode (0-4 oder aus, zimmer, halle, kirche, echo), wet (0-100), ann (0/1), bass, treble (-12 bis 12 dB).
// Read and set the sound effects: mode (0-4 or off, room, hall, church, echo), wet (0-100), ann (0/1), bass, treble (-12 to 12 dB).

int fxModeFrom(String v, int def) {
    v.trim();
    v.toLowerCase();
    if (v.isEmpty()) return def;
    if (v == "aus" || v == "off") return 0;
    if (v == "zimmer" || v == "room") return 1;
    if (v == "halle" || v == "hall") return 2;
    if (v == "kirche" || v == "church") return 3;
    if (v == "echo") return 4;
    if (v.length() == 1 && v[0] >= '0' && v[0] <= '4') return v.toInt();
    return def;
}

void handleApiEffect() {
    if (webserver.method() == HTTP_POST) {
        String m = apiArg("mode");
        if (!m.isEmpty()) {
            int mode = fxModeFrom(m, -1);
            if (mode < 0) return sendErr(400, "mode: aus, zimmer, halle, kirche, echo oder 0-4");
            cfg.fxMode = mode;
            prefs.putInt("fxmode", cfg.fxMode);
        }
        if (!apiArg("wet").isEmpty()) {
            cfg.fxWet = constrain(apiArg("wet").toInt(), 0, 100);
            prefs.putInt("fxwet", cfg.fxWet);
        }
        if (!apiArg("bass").isEmpty()) {
            cfg.eqBass = constrain(apiArg("bass").toInt(), -12, 12);
            prefs.putInt("eqb", cfg.eqBass);
        }
        if (!apiArg("treble").isEmpty()) {
            cfg.eqTreble = constrain(apiArg("treble").toInt(), -12, 12);
            prefs.putInt("eqt", cfg.eqTreble);
        }
        if (!apiArg("pan").isEmpty()) {
            String pv = apiArg("pan");
            pv.trim();
            pv.toLowerCase();
            int pm = -1;
            if (pv == "off" || pv == "aus" || pv == "0") pm = 0;
            else if (pv == "lr" || pv == "1") pm = 1;
            else if (pv == "rl" || pv == "2") pm = 2;
            else if (pv == "pp" || pv == "hin" || pv == "3") pm = 3;
            if (pm < 0) return sendErr(400, "pan: off, lr, rl, pp oder 0-3");
            cfg.panMode = pm;
            prefs.putInt("panm", cfg.panMode);
        }
        if (!apiArg("pansec").isEmpty()) {
            String ps = apiArg("pansec");
            ps.replace(",", ".");
            cfg.panDs = constrain((int)(ps.toFloat() * 10.0f + 0.5f), 5, 200);
            prefs.putInt("pand", cfg.panDs);
        }
        fxApplyCfg();
    }
    static const char* const names[] = {"off", "room", "hall", "church", "echo"};
    static const char* const pnames[] = {"off", "lr", "rl", "pp"};
    sendJson(200, String("{\"ok\":true,\"msg\":\"Gespeichert\",\"mode\":\"") + names[cfg.fxMode] + "\",\"wet\":" + String(cfg.fxWet) + ",\"bass\":" + String(cfg.eqBass) + ",\"treble\":" + String(cfg.eqTreble) + ",\"pan\":\"" + pnames[cfg.panMode] + "\",\"pansec\":" + String(cfg.panDs / 10.0, 1) + ",\"load\":" + String(fx.loadPercent(), 1) + ",\"annMode\":" + String((int)annFx.mode) + ",\"annLoad\":" + String(annFx.loadPercent(), 1) + "}");
}

void handleApiSdMount() {
    bool ok = sdMount();
    if (!ok) return sendErr(400, "SD: " + sdState);
    sendOk("SD-Karte eingebunden");
}

// Dateimanager der SD-Karte: neuer Ordner, loeschen (Datei oder Ordner mit Inhalt), umbenennen und herunterladen.
// File manager of the SD card: new folder, delete (file or folder with content), rename and download.

void handleApiSdMkdir() {
    if (!sdReady) return sendErr(400, "SD-Karte nicht verf\xC3\xBCgbar");
    String dir = apiArg("dir");
    if (dir.isEmpty()) dir = "/";
    if (dir.length() > 1 && dir.endsWith("/")) dir.remove(dir.length() - 1);
    String name = sdCleanName(apiArg("name"), false);
    if (name.isEmpty() || !sdPathOk(dir)) return sendErr(400, "Name oder Ordner nicht erlaubt");
    String path = (dir == "/" ? String() : dir) + "/" + name;
    if (xSemaphoreTake(sdMutex, pdMS_TO_TICKS(3000)) != pdTRUE) return sendErr(400, "SD-Karte ist besch\xC3\xA4" "ftigt");
    bool exists = SD.exists(path.c_str());
    bool ok = !exists && SD.mkdir(path.c_str());
    xSemaphoreGive(sdMutex);
    if (exists) return sendErr(400, "Existiert schon");
    if (!ok) return sendErr(400, "Ordner konnte nicht angelegt werden");
    logLine("[SD] folder created " + path);
    sendOk("Ordner angelegt");
}

void handleApiSdDelete() {
    if (!sdReady) return sendErr(400, "SD-Karte nicht verf\xC3\xBCgbar");
    String path = apiArg("path");
    if (path.length() > 1 && path.endsWith("/")) path.remove(path.length() - 1);
    if (!sdPathOk(path) || path == "/") return sendErr(400, "Pfad nicht erlaubt");
    sdStopIfUsing(path);
    if (xSemaphoreTake(sdMutex, pdMS_TO_TICKS(3000)) != pdTRUE) return sendErr(400, "SD-Karte ist besch\xC3\xA4" "ftigt");
    bool exists = SD.exists(path.c_str());
    bool ok = exists && sdRemoveTree(path, 0);
    xSemaphoreGive(sdMutex);
    if (!exists) return sendErr(404, "Nicht gefunden");
    if (!ok) return sendErr(400, "Konnte nicht gel\xC3\xB6scht werden");
    storageInvalidate();
    logLine("[SD] deleted " + path);
    sendOk("Gel\xC3\xB6scht");
}

void handleApiSdRename() {
    if (!sdReady) return sendErr(400, "SD-Karte nicht verf\xC3\xBCgbar");
    String path = apiArg("path");
    if (path.length() > 1 && path.endsWith("/")) path.remove(path.length() - 1);
    if (!sdPathOk(path) || path == "/") return sendErr(400, "Pfad nicht erlaubt");
    if (xSemaphoreTake(sdMutex, pdMS_TO_TICKS(3000)) != pdTRUE) return sendErr(400, "SD-Karte ist besch\xC3\xA4" "ftigt");
    File f = SD.open(path.c_str());
    bool exists = f;
    bool isDir = f && f.isDirectory();
    if (f) f.close();
    String name = sdCleanName(apiArg("to"), !isDir);
    String parent = path.substring(0, path.lastIndexOf('/'));
    String target = parent + "/" + name;
    bool bad = name.isEmpty();
    bool taken = !bad && SD.exists(target.c_str());
    bool ok = exists && !bad && !taken;
    if (ok) {
        xSemaphoreGive(sdMutex);
        sdStopIfUsing(path);
        xSemaphoreTake(sdMutex, portMAX_DELAY);
        ok = SD.rename(path.c_str(), target.c_str());
    }
    xSemaphoreGive(sdMutex);
    if (!exists) return sendErr(404, "Nicht gefunden");
    if (bad) return sendErr(400, "Neuer Name nicht erlaubt (Dateien enden auf .mp3)");
    if (taken) return sendErr(400, "Der neue Name existiert schon");
    if (!ok) return sendErr(400, "Umbenennen fehlgeschlagen");
    logLine("[SD] renamed " + path + " -> " + target);
    sendOk("Umbenannt");
}

void handleApiSdFile() {
    String path = webserver.arg("path");
    String lower = path;
    lower.toLowerCase();
    if (!sdReady || !sdPathOk(path) || !lower.endsWith(".mp3")) {
        webserver.send(404, "text/plain", "Not found");
        return;
    }
    if (xSemaphoreTake(sdMutex, pdMS_TO_TICKS(3000)) != pdTRUE) {
        webserver.send(503, "text/plain", "busy");
        return;
    }
    File f = SD.open(path.c_str(), FILE_READ);
    size_t size = f ? f.size() : 0;
    xSemaphoreGive(sdMutex);
    if (!f || f.isDirectory()) {
        if (f) f.close();
        webserver.send(404, "text/plain", "Not found");
        return;
    }
    String base = path.substring(path.lastIndexOf('/') + 1);
    webserver.setContentLength(size);
    webserver.sendHeader("Content-Disposition", "attachment; filename=\"" + base + "\"");
    webserver.send(200, "audio/mpeg", "");
    WiFiClient client = webserver.client();
    uint8_t* buf = (uint8_t*)malloc(2048);
    size_t sent = 0;
    while (buf && sent < size && client.connected()) {
        xSemaphoreTake(sdMutex, portMAX_DELAY);
        int n = f.read(buf, 2048);
        xSemaphoreGive(sdMutex);
        if (n <= 0) break;
        client.write(buf, n);
        sent += n;
        if (audio) audio->loop();
        esp_task_wdt_reset();
    }
    free(buf);
    xSemaphoreTake(sdMutex, portMAX_DELAY);
    f.close();
    xSemaphoreGive(sdMutex);
}

void handleApiFiles() {
    String j = "{\"files\":[";
    bool first = true;
    if (fsReady) {
        // Erst der Ordner der MP3-Dateien, dann der Unterordner ansagen (Namen mit Vorsatz ansagen/).
        // First the folder of the MP3 files, then the subfolder ansagen (names with the prefix ansagen/).

        for (int pass = 0; pass < 2; pass++) {
            String dpath = pass == 0 ? String(MP3_DIR) : String(MP3_DIR) + "/" + TTS_FLASH_SUB;
            String prefix = pass == 0 ? String() : String(TTS_FLASH_SUB) + "/";
            File dir = LittleFS.open(dpath);
            File f = dir ? dir.openNextFile() : File();
            while (f) {
                if (!f.isDirectory()) {
                    if (!first) j += ",";
                    first = false;
                    String n = String(f.name());
                    n = n.substring(n.lastIndexOf('/') + 1);
                    j += "{\"name\":\"" + jsonEscape(prefix + n) + "\",\"size\":" + String((unsigned long)f.size()) + "}";
                }
                f = dir.openNextFile();
                audioPump();
            }
            if (dir) dir.close();
        }
    }
    audioPump();
    storageRefresh();
    j += "],\"used\":" + String(fsReady ? fsUsedC : 0) + ",\"total\":" + String(fsReady ? fsTotalC : 0) + "}";
    sendJson(200, j);
}

// MP3-Datei im Geraet umbenennen: file = alter Name, to = neuer Name (".mp3" wird bei Bedarf angehaengt). Pins, die diese Datei abspielen, folgen dem neuen Namen.
// Rename an MP3 file in the device: file = old name, to = new name (".mp3" is appended if missing). Pins that play this file follow the new name.

// Inhalt eines Ordners im Flash wie bei der SD-Karte: dir leer = Ordner der MP3-Dateien (mit dem Unterordner ansagen), dir=ansagen = die gespeicherten Texte.
// Content of a folder in flash like on the SD card: empty dir = folder of the MP3 files (with the subfolder ansagen), dir=ansagen = the saved texts.

void handleApiFlash() {
    String dir = webserver.arg("dir");
    while (dir.startsWith("/")) dir.remove(0, 1);
    if (dir.endsWith("/")) dir.remove(dir.length() - 1);
    if (!dir.isEmpty() && dir != TTS_FLASH_SUB) return sendErr(404, "Ordner nicht gefunden");
    std::vector<std::pair<String, uint32_t>> files;
    bool hasSub = false;
    if (fsReady) {
        File d = LittleFS.open(String(MP3_DIR) + (dir.isEmpty() ? String() : "/" + dir));
        File f = d ? d.openNextFile() : File();
        while (f) {
            String n = String(f.name());
            n = n.substring(n.lastIndexOf('/') + 1);
            if (f.isDirectory()) {
                if (dir.isEmpty() && n == TTS_FLASH_SUB) hasSub = true;
            } else {
                files.push_back(std::make_pair(n, (uint32_t)f.size()));
            }
            f = d.openNextFile();
            audioPump();
        }
        if (d) d.close();
    }
    std::sort(files.begin(), files.end(), [](const std::pair<String, uint32_t>& a, const std::pair<String, uint32_t>& b) {
        String x = a.first, y = b.first;
        x.toLowerCase();
        y.toLowerCase();
        return x < y;
    });
    storageRefresh();
    String j = "{\"dir\":\"" + dir + "\",\"entries\":[";
    bool first = true;
    if (hasSub) {
        j += "{\"n\":\"" TTS_FLASH_SUB "\",\"d\":1,\"s\":0}";
        first = false;
    }
    for (size_t i = 0; i < files.size(); i++) {
        if (!first) j += ",";
        first = false;
        j += "{\"n\":\"" + jsonEscape(files[i].first) + "\",\"d\":0,\"s\":" + String((unsigned long)files[i].second) + "}";
    }
    j += "],\"used\":" + String(fsReady ? fsUsedC : 0) + ",\"total\":" + String(fsReady ? fsTotalC : 0) + "}";
    sendJson(200, j);
}

void handleApiRename() {
    String oldName = cleanFileName(apiArg("file"));
    String to = apiArg("to");
    to.trim();
    String lower = to;
    lower.toLowerCase();
    if (!to.isEmpty() && !lower.endsWith(".mp3")) to += ".mp3";
    if (oldName.startsWith("ansagen/") && !to.startsWith("ansagen/") && !to.isEmpty()) to = "ansagen/" + to;
    String newName = cleanFileName(to);
    String oldPath = String(MP3_DIR) + "/" + oldName;
    String newPath = String(MP3_DIR) + "/" + newName;
    if (oldName.isEmpty() || !LittleFS.exists(oldPath)) return sendErr(404, "Datei nicht gefunden");
    if (newName.isEmpty()) return sendErr(400, "Neuer Name nicht erlaubt (Dateien enden auf .mp3)");
    if (newName == oldName) return sendErr(400, "Der neue Name ist gleich dem alten");
    if (LittleFS.exists(newPath)) return sendErr(400, "Der neue Name existiert schon");
    stopIfUsing(oldName);
    if (!LittleFS.rename(oldPath, newPath)) return sendErr(400, "Umbenennen fehlgeschlagen");
    for (int pin = 1; pin <= 48; pin++) {
        if (pinType[pin] == "file" && pinText[pin] == oldName) {
            pinText[pin] = newName;
            prefs.putString(("px" + String(pin)).c_str(), newName);
        }
    }
    logLine("[FILES] renamed " + oldPath + " -> " + newPath);
    sendOk("Umbenannt");
}

// Liefert eine MP3-Datei aus dem Flash zum Herunterladen (fuer die Sicherung); in Stuecken, der Audio-Puffer wird zwischendurch nachgeladen.
// Delivers an MP3 file from flash for download (for the backup); in pieces, the audio buffer is refilled in between.

void handleApiFileGet() {
    String name = cleanFileName(webserver.arg("file"));
    String path = String(MP3_DIR) + "/" + name;
    if (name.isEmpty() || !LittleFS.exists(path)) return sendErr(404, "Datei nicht gefunden");
    File f = LittleFS.open(path, FILE_READ);
    if (!f) return sendErr(404, "Datei nicht gefunden");
    webserver.sendHeader("Cache-Control", "no-store");
    webserver.setContentLength(f.size());
    webserver.send(200, "audio/mpeg", "");
    uint8_t buf[1024];
    while (f.available()) {
        int n = f.read(buf, sizeof(buf));
        if (n <= 0) break;
        webserver.sendContent((const char*)buf, n);
        audioPump();
    }
    f.close();
}

void handleApiDelete() {

    // Der Unterordner ansagen wird samt Inhalt geloescht.
    // The subfolder ansagen is deleted together with its content.

    String rawName = webserver.arg("file");
    if (rawName == TTS_FLASH_SUB || rawName == String(TTS_FLASH_SUB) + "/") {
        String dpath = String(MP3_DIR) + "/" + TTS_FLASH_SUB;
        std::vector<String> names;
        File d = LittleFS.open(dpath);
        if (!d || !d.isDirectory()) return sendErr(404, "Ordner nicht gefunden");
        File f = d.openNextFile();
        while (f) {
            String n = String(f.name());
            names.push_back(n.substring(n.lastIndexOf('/') + 1));
            f = d.openNextFile();
        }
        d.close();
        for (size_t i = 0; i < names.size(); i++) {
            stopIfUsing(String(TTS_FLASH_SUB) + "/" + names[i]);
            LittleFS.remove(dpath + "/" + names[i]);
            audioPump();
        }
        LittleFS.rmdir(dpath);
        storageInvalidate();
        logLine("[FILES] deleted folder " + dpath);
        return sendOk("Gel\xC3\xB6scht");
    }
    String name = cleanFileName(webserver.arg("file"));
    String path = String(MP3_DIR) + "/" + name;
    if (name.isEmpty() || !LittleFS.exists(path)) return sendErr(404, "Datei nicht gefunden");
    stopIfUsing(name);
    LittleFS.remove(path);
    storageInvalidate();
    logLine("[FILES] deleted " + path);
    sendOk("Gel\xC3\xB6scht");
}

File uploadFile;
String uploadError;
bool uploadOnSd = false;
bool uploadOnLang = false;

// Sprachdateien: /lang_<code>.json im Speicher des Geraets; der Code sind zwei bis acht Kleinbuchstaben (zum Beispiel en).
// Language files: /lang_<code>.json in the device storage; the code is two to eight lowercase letters (for example en).

String langCode(String s) {
    s.toLowerCase();
    if (s.endsWith(".json")) s.remove(s.length() - 5);
    if (s.length() < 2 || s.length() > 8) return "";
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] < 'a' || s[i] > 'z') return "";
    }
    return s;
}

void handleLangJson() {
    String c = langCode(webserver.arg("l"));
    String path = "/lang_" + c + ".json";
    if (c.isEmpty() || !fsReady || !LittleFS.exists(path)) return sendErr(404, "Sprache nicht gefunden");
    File f = LittleFS.open(path, FILE_READ);
    webserver.sendHeader("Cache-Control", "no-cache");
    webserver.streamFile(f, "application/json");
    f.close();
}

void handleApiPins() {
    String pinArg = apiArg("pin");
    if (pinArg.length() > 0) {
        int pin = pinArg.toInt();
        if (pin < 1 || pin > 48 || !pinIdle(pin)) return sendErr(400, "Pin nicht verf\xC3\xBCgbar");
        String type = apiArg("type");
        bool control = pinTypeIsControl(type);
        if (type != "say" && type != "file" && type != "station" && !control) type = "";
        String text = apiArg("text");
        text.trim();
        if (text.length() > 300) return sendErr(400, "Text zu lang (max. 300 Zeichen)");
        if (text.isEmpty() && !control) type = "";
        int vol = apiArg("vol").length() > 0 ? constrain(apiArg("vol").toInt(), 0, VOLUME_MAX) : -1;
        pinType[pin] = type;
        pinText[pin] = text;
        pinVol[pin] = vol;
        prefs.putString(("pt" + String(pin)).c_str(), type);
        prefs.putString(("px" + String(pin)).c_str(), text);
        prefs.putInt(("pv" + String(pin)).c_str(), vol);
        logLine("[PIN] GPIO " + String(pin) + " set: " + (type.isEmpty() ? String("no action") : type + " \"" + text + "\""));
        return sendOk("Gespeichert");
    }
    String j = "{\"pins\":[";
    bool first = true;
    for (int pin = 1; pin <= 48; pin++) {
        if (!pinIdle(pin)) continue;
        if (!first) j += ",";
        first = false;
        j += "{\"p\":" + String(pin) + ",\"l\":" + String(digitalRead(pin) == LOW ? 0 : 1) + ",\"t\":\"" + pinType[pin] + "\",\"x\":\"" + jsonEscape(pinText[pin]) + "\",\"v\":" + String(pinVol[pin]) + "}";
    }
    sendJson(200, j + "]}");
}

// Sprachdatei vom Projekt auf GitHub laden (feste Adresse, nur der Sprachcode kommt von aussen) und als /lang_<code>.json ablegen.
// Load a language file from the project on GitHub (fixed address, only the language code comes from outside) and store it as /lang_<code>.json.

#define LANG_GITHUB_BASE "https://raw.githubusercontent.com/holgiw/ESP32-netspeaker/main/lang/"

bool langFetch(const String& code, String& err) {
    if (WiFi.status() != WL_CONNECTED) {
        err = "Keine WLAN-Verbindung";
        return false;
    }
    if (ESP.getFreeHeap() < 70000) {
        err = "Zu wenig freier Speicher (Webradio kurz stoppen)";
        return false;
    }
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    http.useHTTP10(true);
    http.setTimeout(10000);
    http.setConnectTimeout(10000);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    if (!http.begin(client, String(LANG_GITHUB_BASE) + code + ".json")) {
        err = "HTTP begin failed";
        return false;
    }
    esp_task_wdt_reset();
    int rc = http.GET();
    esp_task_wdt_reset();
    if (rc != HTTP_CODE_OK) {
        err = rc == 404 ? String("Sprachdatei nicht gefunden: ") + code + ".json" : "GitHub HTTP " + String(rc);
        http.end();
        return false;
    }
    LittleFS.remove("/lang_tmp.json");
    File f = LittleFS.open("/lang_tmp.json", FILE_WRITE);
    if (!f) {
        err = "Datei kann nicht angelegt werden";
        http.end();
        return false;
    }
    WiFiClient* s = http.getStreamPtr();
    uint8_t buf[1024];
    size_t total = 0;
    uint8_t first = 0, last = 0;
    unsigned long deadline = millis() + 30000UL;
    bool ok = true;
    while ((http.connected() || s->available()) && millis() < deadline) {
        int n = s->available();
        if (n <= 0) {
            delay(5);
            esp_task_wdt_reset();
            continue;
        }
        if (n > (int)sizeof(buf)) n = sizeof(buf);
        n = s->readBytes(buf, n);
        if (n <= 0) break;
        for (int i = 0; i < n; i++) {
            if (buf[i] > ' ') {
                if (first == 0) first = buf[i];
                last = buf[i];
            }
        }
        total += n;
        if (total > 262144) {
            ok = false;
            err = "Datei zu gross";
            break;
        }
        if (f.write(buf, n) != (size_t)n) {
            ok = false;
            err = "Speicher voll";
            break;
        }
        if (audio) audio->loop();
        esp_task_wdt_reset();
    }
    f.close();
    http.end();
    if (ok && (total < 10 || first != '{' || last != '}')) {
        ok = false;
        err = "Keine gueltige Sprachdatei";
    }
    if (!ok) {
        LittleFS.remove("/lang_tmp.json");
        return false;
    }
    String dest = "/lang_" + code + ".json";
    LittleFS.remove(dest);
    LittleFS.rename("/lang_tmp.json", dest);
    logLine("[LANG] " + code + ".json loaded from GitHub (" + String((unsigned long)total) + " bytes)");
    return true;
}

#define STATIONS_GITHUB_BASE "https://raw.githubusercontent.com/holgiw/ESP32-netspeaker/main/stations/"

// Fertige Senderliste (Textdatei im Ordner stations des Projekts) von GitHub holen; nur der Listenname kommt von aussen.
// Fetch a ready-made station list (text file in the folder stations of the project) from GitHub; only the list name comes from outside.

bool stationListFetch(const String& name, String& body, String& err) {
    if (WiFi.status() != WL_CONNECTED) {
        err = "Keine WLAN-Verbindung";
        return false;
    }
    if (ESP.getFreeHeap() < 70000) {
        err = "Zu wenig freier Speicher (Webradio kurz stoppen)";
        return false;
    }
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    http.useHTTP10(true);
    http.setTimeout(10000);
    http.setConnectTimeout(10000);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int rc = -1;

    // Der erste Verbindungsversuch scheitert gelegentlich (rc -1); ein zweiter nach kurzer Pause klappt dann.
    // The first connection attempt occasionally fails (rc -1); a second one after a short pause then works.

    for (int attempt = 0; attempt < 2 && rc < 0; attempt++) {
        if (attempt > 0) {
            http.end();
            delay(800);
        }
        if (!http.begin(client, String(STATIONS_GITHUB_BASE) + name + ".txt")) {
            err = "HTTP begin failed";
            return false;
        }
        esp_task_wdt_reset();
        rc = http.GET();
        esp_task_wdt_reset();
    }
    if (rc != HTTP_CODE_OK) {
        err = rc == 404 ? String("Senderliste nicht gefunden: ") + name : "GitHub HTTP " + String(rc);
        http.end();
        return false;
    }
    if (http.getSize() > 20000) {
        err = "Datei zu gross";
        http.end();
        return false;
    }
    body = http.getString();
    http.end();
    return true;
}

void handleApiStationList() {
    String name = apiArg("list");
    name.trim();
    name.toLowerCase();
    if (name.endsWith(".txt")) name.remove(name.length() - 4);
    bool okName = name.length() >= 1 && name.length() <= 32;
    for (size_t i = 0; i < name.length() && okName; i++) {
        char c = name[i];
        okName = (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-';
    }
    if (!okName) return sendErr(400, "Name der Liste: Kleinbuchstaben, Ziffern und Bindestrich, zum Beispiel aac-auswahl");
    String body, err;
    if (!stationListFetch(name, body, err)) return sendErr(502, err);
    String res = stationsApply(body);
    if (res.startsWith("OK|")) return sendOk(res.substring(3));
    sendErr(422, res.substring(5));
}


void favSaveFrom(int first) {
    (void)first;
    favSaveAll();
}

int favCount() {
    int n = 0;
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (!favUrl[i].isEmpty()) n++;
    }
    return n;
}

void handleApiFavorites() {
    favEnsure();
    String j = "{\"max\":" + String(FAV_SLOTS) + ",\"favorites\":[";
    bool first = true;
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (favUrl[i].isEmpty()) continue;
        if (!first) j += ",";
        first = false;
        j += "{\"n\":" + String(i + 1) + ",\"name\":\"" + jsonEscape(favName[i]) + "\",\"url\":\"" + jsonEscape(favUrl[i]) + "\"}";
    }
    j += "]}";
    sendJson(200, j);
}

void handleApiFavoriteAdd() {
    favEnsure();
    String url = apiArg("url");
    url.trim();
    String name = apiArg("name");
    name.trim();
    name.replace("\r", " ");
    name.replace("\n", " ");
    if (!(url.startsWith("http://") || url.startsWith("https://"))) return sendErr(400, "URL muss mit http:// oder https:// beginnen");
    if (url.length() > RADIO_URL_MAX) return sendErr(400, "URL zu lang");
    if (name.isEmpty()) name = url.substring(url.indexOf("//") + 2);
    if (name.length() > RADIO_NAME_MAX) name = name.substring(0, RADIO_NAME_MAX);
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (favUrl[i] == url) return sendOk("Schon in den Favoriten");
    }
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (favUrl[i].isEmpty()) {
            favName[i] = name;
            favUrl[i] = url;
            favSaveFrom(i);
            logLine("[WEB] favorite added: " + name);
            return sendOk("Zu den Favoriten hinzugef\xC3\xBCgt");
        }
    }
    sendErr(400, "Favoriten voll (" + String(FAV_SLOTS) + ")");
}

void handleApiFavoriteDelete() {
    favEnsure();
    int n = apiArg("n").toInt();
    if (n < 1 || n > FAV_SLOTS || favUrl[n - 1].isEmpty()) return sendErr(404, "Favorit nicht gefunden");
    for (int i = n - 1; i < FAV_SLOTS - 1; i++) {
        favName[i] = favName[i + 1];
        favUrl[i] = favUrl[i + 1];
    }
    favName[FAV_SLOTS - 1] = "";
    favUrl[FAV_SLOTS - 1] = "";
    favSaveFrom(n - 1);
    logLine("[WEB] favorite " + String(n) + " deleted");
    sendOk("Favorit gel\xC3\xB6scht");
}

// Favoriten als neue Senderliste uebernehmen (ersetzt die gespeicherte Senderliste).
// Take the favorites over as the new station list (replaces the stored station list).

void handleApiFavoritesToList() {
    favEnsure();
    String t = "# " PROJECT_NAME " stations\n";
    int k = 0;
    for (int i = 0; i < FAV_SLOTS; i++) {
        if (favUrl[i].isEmpty()) continue;
        k++;
        t += "rn" + String(k) + "=" + favName[i] + "\nru" + String(k) + "=" + favUrl[i] + "\nrv" + String(k) + "=\n";
    }
    if (k == 0) return sendErr(400, "Keine Favoriten");
    String res = stationsApply(t);
    if (res.startsWith("OK|")) return sendOk(res.substring(3));
    sendErr(400, res.startsWith("FAIL|") ? res.substring(5) : res);
}
void handleApiLang() {
    if (webserver.method() == HTTP_POST) {
        String d = langCode(apiArg("delete"));
        if (!d.isEmpty() && fsReady) LittleFS.remove("/lang_" + d + ".json");
        if (apiArg("fetch").length() > 0) {
            String fc = langCode(apiArg("fetch"));
            String err;
            if (fc.isEmpty() || !fsReady) return sendErr(400, "Dateiname wie en.json (zwei bis acht Kleinbuchstaben)");
            if (!langFetch(fc, err)) return sendErr(502, err);
            return sendOk("Geladen");
        }
    }
    String j = "{\"langs\":[";
    bool first = true;
    if (fsReady) {
        File dir = LittleFS.open("/");
        File f = dir ? dir.openNextFile() : File();
        while (f) {
            String n = String(f.name());
            n = n.substring(n.lastIndexOf('/') + 1);
            if (!f.isDirectory() && n.startsWith("lang_") && n.endsWith(".json")) {
                if (!first) j += ",";
                first = false;
                j += "\"" + n.substring(5, n.length() - 5) + "\"";
            }
            f = dir.openNextFile();
        }
    }
    sendJson(200, j + "]}");
}

void handleUploadData() {
    HTTPUpload& up = webserver.upload();
    if (up.status == UPLOAD_FILE_START) {
        uploadError = "";
        uploadOnSd = webserver.arg("target") == "sd";
        uploadOnLang = webserver.arg("target") == "lang";
        if (uploadOnLang) {
            String c = langCode(up.filename);
            if (c.isEmpty()) {
                uploadError = "Dateiname wie en.json (zwei bis acht Kleinbuchstaben)";
            } else {
                uploadFile = LittleFS.open("/lang_" + c + ".json", FILE_WRITE);
                if (!uploadFile) uploadError = "Datei kann nicht angelegt werden";
            }
        } else if (uploadOnSd) {
            String dir = webserver.arg("dir");
            if (dir.isEmpty()) dir = "/";
            String name = sdCleanName(up.filename, true);
            if (!sdReady) {
                uploadError = "SD-Karte nicht verf\xC3\xBCgbar";
            } else if (!sdPathOk(dir)) {
                uploadError = "Ordner nicht erlaubt";
            } else if (name.isEmpty()) {
                uploadError = "Dateiname oder Typ nicht erlaubt";
            } else {
                if (dir.length() > 1 && dir.endsWith("/")) dir.remove(dir.length() - 1);
                String path = (dir == "/" ? String() : dir) + "/" + name;
                sdStopIfUsing(path);
                if (xSemaphoreTake(sdMutex, pdMS_TO_TICKS(3000)) == pdTRUE) {
                    File d = SD.open(dir.c_str());
                    if (d && d.isDirectory()) uploadFile = SD.open(path.c_str(), FILE_WRITE);
                    else uploadError = "Ordner nicht gefunden";
                    if (d) d.close();
                    xSemaphoreGive(sdMutex);
                } else {
                    uploadError = "SD-Karte ist besch\xC3\xA4" "ftigt";
                }
                if (uploadError.isEmpty() && !uploadFile) uploadError = "Datei kann nicht angelegt werden";
            }
        } else {
            String sub = webserver.arg("dir") == TTS_FLASH_SUB ? String(TTS_FLASH_SUB) + "/" : String();
            String name = cleanFileName(sub + up.filename);
            if (!name.isEmpty()) stopIfUsing(name);
            if (name.isEmpty()) {
                uploadError = "Dateiname oder Typ nicht erlaubt";
            } else {
                if (sub.length() > 0 && !LittleFS.exists(String(MP3_DIR) + "/" + TTS_FLASH_SUB)) LittleFS.mkdir(String(MP3_DIR) + "/" + TTS_FLASH_SUB);
                uploadFile = LittleFS.open(String(MP3_DIR) + "/" + name, FILE_WRITE);
                if (!uploadFile) uploadError = "Datei kann nicht angelegt werden";
            }
        }
    } else if (up.status == UPLOAD_FILE_WRITE) {
        if (uploadFile) {
            if (uploadOnSd) xSemaphoreTake(sdMutex, portMAX_DELAY);
            size_t written = uploadFile.write(up.buf, up.currentSize);
            if (written != up.currentSize) {
                uploadError = "Speicher voll";
                uploadFile.close();
            }
            if (uploadOnSd) xSemaphoreGive(sdMutex);
        }

        // Ein laufendes Webradio weiter versorgen, solange der Upload die Hauptschleife belegt.
        // Keep feeding a running web radio while the upload occupies the main loop.

        if (audio) audio->loop();
        audioEventPump();
        esp_task_wdt_reset();
    } else if (up.status == UPLOAD_FILE_END) {
        if (uploadFile) {
            if (uploadOnSd) xSemaphoreTake(sdMutex, portMAX_DELAY);
            uploadFile.close();
            if (uploadOnSd) xSemaphoreGive(sdMutex);
        }
        if (uploadError.isEmpty()) logLine("[FILES] uploaded " + up.filename + " (" + String((unsigned long)up.totalSize) + " bytes)");
    } else if (up.status == UPLOAD_FILE_ABORTED) {
        if (uploadFile) {
            if (uploadOnSd) xSemaphoreTake(sdMutex, portMAX_DELAY);
            uploadFile.close();
            if (uploadOnSd) xSemaphoreGive(sdMutex);
        }
        uploadError = "Abgebrochen";
    }
}

void handleUploadDone() {
    if (uploadError.length() > 0) return sendErr(400, uploadError);
    storageInvalidate();
    sendOk("Hochgeladen");
}

// Alle WLANs im Umkreis, nach Signalstaerke sortiert, ohne Doppelte; waehrend OTA nie suchen.
// All WiFi networks nearby, sorted by signal strength, without duplicates; never scan during OTA.

void handleApiScan() {
    int n = WiFi.scanNetworks();
    String names[24];
    int rssi[24];
    int count = 0;
    for (int i = 0; i < n && count < 24; i++) {
        String s = WiFi.SSID(i);
        if (s.isEmpty()) continue;
        bool dup = false;
        for (int k = 0; k < count; k++) {
            if (names[k] == s) {
                dup = true;
                if (WiFi.RSSI(i) > rssi[k]) rssi[k] = WiFi.RSSI(i);
            }
        }
        if (dup) continue;
        names[count] = s;
        rssi[count] = WiFi.RSSI(i);
        count++;
    }
    WiFi.scanDelete();
    for (int a = 0; a < count; a++) {
        for (int b = a + 1; b < count; b++) {
            if (rssi[b] > rssi[a]) {
                String t = names[a]; names[a] = names[b]; names[b] = t;
                int r = rssi[a]; rssi[a] = rssi[b]; rssi[b] = r;
            }
        }
    }
    String j = "[";
    for (int i = 0; i < count; i++) j += String(i ? "," : "") + "\"" + jsonEscape(names[i]) + "\"";
    sendJson(200, j + "]");
}

// WLAN-Tab: Hostname, Plaetze loeschen / nach vorn holen, nicht blockierende Suche mit Zwischenspeicher.
// WiFi tab: hostname, delete slots / move to front, non-blocking scan with a cache.

bool isPrivateClient() {
    IPAddress ip = webserver.client().remoteIP();
    return ip[0] == 10 || ip[0] == 127 || (ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31) || (ip[0] == 192 && ip[1] == 168) || (ip[0] == 169 && ip[1] == 254);
}

void saveWifiSlots() {
    for (int i = 0; i < 3; i++) {
        prefs.putString(("ssid" + String(i + 1)).c_str(), cfg.ssid[i]);
        prefs.putString(("pass" + String(i + 1)).c_str(), cfg.pass[i]);
    }
}

void handleSetHostname() {
    String host = cleanHost(webserver.arg("host"));
    if (host.isEmpty()) {
        redirectTab("wlan", "hostbad");
        return;
    }
    bool changed = host != cfg.host;
    cfg.host = host;
    prefs.putString("host", host);
    logLine("[WEB] hostname set: " + host);
    redirectTab("wlan", changed ? "restart" : "saved");
}

void handleDeleteWifi() {
    int idx = webserver.arg("index").toInt();
    if (idx < 0 || idx > 2 || cfg.ssid[idx].isEmpty()) {
        redirectTab("wlan", "saved");
        return;
    }
    if (!isPrivateClient()) {
        redirectTab("wlan", "wifiprivate");
        return;
    }
    bool wasActive = WiFi.status() == WL_CONNECTED && WiFi.SSID() == cfg.ssid[idx];
    for (int k = idx; k < 2; k++) {
        cfg.ssid[k] = cfg.ssid[k + 1];
        cfg.pass[k] = cfg.pass[k + 1];
    }
    cfg.ssid[2] = "";
    cfg.pass[2] = "";
    saveWifiSlots();
    logLine("[WEB] WiFi slot " + String(idx + 1) + " deleted");
    if (wasActive) restartAt = millis() + 500;
    else wifiRetryNow();
    redirectTab("wlan", "wifideleted");
}

// "Verbinden": das gewaehlte Netz rueckt an die erste Stelle und das Geraet startet neu (Verbinden blockiert bis zu 30 s).
// "Connect": the chosen network moves to the first place and the device restarts (connecting blocks for up to 30 s).

void handleConnectWifi() {
    int idx = webserver.arg("index").toInt();
    if (idx < 0 || idx > 2 || cfg.ssid[idx].isEmpty()) {
        redirectTab("wlan", "saved");
        return;
    }
    if (!isPrivateClient()) {
        redirectTab("wlan", "wifiprivate");
        return;
    }
    if (idx > 0) {
        String s = cfg.ssid[idx], p = cfg.pass[idx];
        for (int k = idx; k > 0; k--) {
            cfg.ssid[k] = cfg.ssid[k - 1];
            cfg.pass[k] = cfg.pass[k - 1];
        }
        cfg.ssid[0] = s;
        cfg.pass[0] = p;
        saveWifiSlots();
    }
    logLine("[WEB] WiFi connect to slot " + String(idx + 1));
    restartAt = millis() + 500;
    redirectTab("wlan", "wifiswitch");
}

String scanJson = "[]";
bool scanHave = false;

// Die Suche laeuft im Hintergrund (scanNetworks(true)); die Seite fragt das Ergebnis ab und bekommt bis dahin den letzten Stand.
// The scan runs in the background (scanNetworks(true)); the page asks for the result and gets the last state until then.

void handleApiScanWifi() {
    int c = WiFi.scanComplete();
    if (c >= 0) {
        String names[24];
        int rssi[24], enc[24];
        int count = 0;
        for (int i = 0; i < c && count < 24; i++) {
            String s = WiFi.SSID(i);
            if (s.isEmpty()) continue;
            bool dup = false;
            for (int k = 0; k < count; k++) {
                if (names[k] == s) {
                    dup = true;
                    if (WiFi.RSSI(i) > rssi[k]) rssi[k] = WiFi.RSSI(i);
                }
            }
            if (dup) continue;
            names[count] = s;
            rssi[count] = WiFi.RSSI(i);
            enc[count] = WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? 0 : 1;
            count++;
        }
        WiFi.scanDelete();
        for (int a = 0; a < count; a++) {
            for (int b = a + 1; b < count; b++) {
                if (rssi[b] > rssi[a]) {
                    String t = names[a]; names[a] = names[b]; names[b] = t;
                    int r = rssi[a]; rssi[a] = rssi[b]; rssi[b] = r;
                    int e = enc[a]; enc[a] = enc[b]; enc[b] = e;
                }
            }
        }
        String j = "[";
        for (int i = 0; i < count; i++) j += String(i ? "," : "") + "{\"ssid\":\"" + jsonEscape(names[i]) + "\",\"rssi\":" + String(rssi[i]) + ",\"enc\":" + String(enc[i]) + "}";
        scanJson = j + "]";
        scanHave = true;
    } else if (c == WIFI_SCAN_FAILED && !scanHave) {
        WiFi.scanNetworks(true);
    }
    sendJson(200, scanJson);
}

void handleApiRescanWifi() {
    if (WiFi.scanComplete() != WIFI_SCAN_RUNNING) {
        WiFi.scanDelete();
        WiFi.scanNetworks(true);
    }
    sendOk("Scan gestartet");
}

// Eigene NTP-Abfrage, unabhaengig von der eingestellten Systemzeit; Antwort "OK|<UTC-Zeit>" oder "FAILED".
// Own NTP query, independent of the configured system time; answer "OK|<UTC time>" or "FAILED".

void handleTestNtp() {
    String server = webserver.arg("server");
    server.trim();
    webserver.sendHeader("Cache-Control", "no-store");
    IPAddress ip;
    if (server.isEmpty() || WiFi.status() != WL_CONNECTED || !WiFi.hostByName(server.c_str(), ip)) {
        webserver.send(200, "text/plain", "FAILED");
        return;
    }
    WiFiUDP udp;
    uint8_t pkt[48] = {0};
    pkt[0] = 0x1B;
    udp.begin(12300 + (millis() % 1000));
    udp.beginPacket(ip, 123);
    udp.write(pkt, 48);
    udp.endPacket();
    unsigned long start = millis();
    while (millis() - start < 1500) {
        if (udp.parsePacket() >= 48) {
            udp.read(pkt, 48);
            uint32_t secs = ((uint32_t)pkt[40] << 24) | ((uint32_t)pkt[41] << 16) | ((uint32_t)pkt[42] << 8) | pkt[43];
            if (secs < 2208988800UL) break;
            time_t epoch = (time_t)(secs - 2208988800UL);
            struct tm timeinfo;
            gmtime_r(&epoch, &timeinfo);
            char buf[32];
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
            udp.stop();
            webserver.send(200, "text/plain", String("OK|") + buf + " UTC");
            return;
        }
        delay(10);
    }
    udp.stop();
    webserver.send(200, "text/plain", "FAILED");
}

String brokerJson() {
    String groups;
    for (int i = 0; i < 5; i++) groups += String(i > 0 ? "," : "") + "\"" + jsonEscape(cfg.mqttGroup[i]) + "\"";
    return "{\"broker\":\"" + jsonEscape(cfg.mqttServer) + "\",\"port\":" + String(cfg.mqttPort) + ",\"user\":\"" + jsonEscape(cfg.mqttUser) + "\",\"groups\":[" + groups + "],\"ha\":" + (cfg.haDisc ? "true" : "false") + ",\"connected\":" + (mqttClient.connected() ? "true" : "false") + "}";
}

void handleApiMqtt() {
    if (webserver.method() == HTTP_POST) {
        if (webserver.hasArg("broker")) {
            String b = webserver.arg("broker");
            b.trim();
            if (b.isEmpty() || b.length() > 63) return sendErr(400, "broker invalid");
            if (webserver.hasArg("port")) {
                int p = webserver.arg("port").toInt();
                if (p < 1 || p > 65535) return sendErr(400, "port invalid");
            }
            cfg.mqttServer = b;
            prefs.putString("mq_srv", b);
        }
        if (webserver.hasArg("port")) {
            int p = webserver.arg("port").toInt();
            if (p < 1 || p > 65535) return sendErr(400, "port invalid");
            cfg.mqttPort = p;
            prefs.putInt("mq_port", p);
        }
        if (webserver.hasArg("user")) {
            cfg.mqttUser = webserver.arg("user");
            cfg.mqttUser.trim();
            if (cfg.mqttUser.isEmpty()) cfg.mqttPass = "";
            prefs.putString("mq_usr", cfg.mqttUser);
            prefs.putString("mq_pw", cfg.mqttPass);
        }
        if (webserver.hasArg("pass") && cfg.mqttUser.length() > 0) {
            cfg.mqttPass = webserver.arg("pass");
            prefs.putString("mq_pw", cfg.mqttPass);
        }
        for (int i = 1; i <= 5; i++) {
            if (!webserver.hasArg("group" + String(i))) continue;
            String g = webserver.arg("group" + String(i));
            g.trim();
            cfg.mqttGroup[i - 1] = g;
            prefs.putString(("mq_g" + String(i)).c_str(), g);
        }
        if (webserver.hasArg("ha")) {
            bool on = flagOn(webserver.arg("ha"));
            if (cfg.haDisc && !on) haRemovePending = true;
            cfg.haDisc = on;
            prefs.putBool("mq_ha", on);
        }
        mqttReconnectNow();
        logLine("[MQTT] Broker set via API: " + cfg.mqttServer + ":" + String(cfg.mqttPort));
    }
    sendJson(200, brokerJson());
}

// Dieselben Bedingungen wie topbarHtml(): Erstansicht und Abfrage muessen uebereinstimmen.
// Same conditions as topbarHtml(): first paint and poll must agree.

void handleTopbarStatus() {
    String mq = mqttDotState(), vo = voiceDotState(), au = audioDotState(), ti = timeDotState();
    String j = "{\"mqtt\":\"" + mq + "\",\"mqttPresent\":" + (mqttGatedPresent() ? "true" : "false");
    j += ",\"voice\":\"" + vo + "\",\"voicePresent\":" + (voiceGatedPresent() ? "true" : "false");
    j += ",\"audio\":\"" + au + "\",\"time\":\"" + ti + "\"";
    j += ",\"volValue\":\"" + String(cfg.vol) + "/" + String(VOLUME_MAX) + "\"";
    j += ",\"datetime\":\"" + formatNow() + "\"";
    j += ",\"mqttTitle\":\"" + dotStatusText("MQTT", mq) + "\",\"voiceTitle\":\"" + dotStatusText("VoiceRSS", vo) + "\"";
    j += ",\"audioTitle\":\"" + dotStatusText("Audio", au) + "\",\"timeTitle\":\"" + dotStatusText("Zeit", ti) + "\"";
    j += ",\"version\":\"" + String(FIRMWARE_MARKER + FIRMWARE_MARKER_PREFIX_LEN) + "\"}";
    sendJson(200, j);
}

void handleVersion() {
    webserver.sendHeader("Cache-Control", "no-store");
    webserver.send(200, "text/plain", String(FIRMWARE_MARKER + FIRMWARE_MARKER_PREFIX_LEN));
}

void handleLog() {
    webserver.sendHeader("Cache-Control", "no-store");
    String out;
    if (fsReady) {
        File old = LittleFS.open(LOG_OLD_FILE, FILE_READ);
        if (old) {
            out += old.readString();
            old.close();
        }
        File cur = LittleFS.open(LOG_FILE, FILE_READ);
        if (cur) {
            out += cur.readString();
            cur.close();
        }
    }
    if (!cfg.logEnabled) out = "[Logging ist ausgeschaltet - Schalter oben im Tab Log]\n" + out;
    sendPumped(200, "text/plain; charset=utf-8", out);
}

void handleRestart() {
    webserver.send(200, "text/plain", "restarting");
    logLine("[WEB] restart requested");
    delay(300);
    ESP.restart();
}

void handleFavicon() {
    webserver.sendHeader("Cache-Control", "public, max-age=86400");
    webserver.send(200, "image/svg+xml",
                   "<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 32 32'>"
                   "<circle cx='16' cy='16' r='14' fill='#10151a' stroke='#f5a623' stroke-width='2.5'/>"
                   "<path d='M10 13v6M14 10v12M18 12v8M22 14v4' stroke='#f5a623' stroke-width='2.5' stroke-linecap='round'/></svg>");
}

void setupWeb() {
    webserver.on("/", HTTP_GET, handleRoot);
    webserver.on("/save", HTTP_POST, handleSave);
    webserver.on("/export", HTTP_GET, handleExport);
    webserver.on("/import", HTTP_POST, handleImport);
    webserver.on("/stations.txt", HTTP_GET, handleStationsExport);
    webserver.on("/importstations", HTTP_POST, handleStationsImport);
    webserver.on("/favorites.txt", HTTP_GET, handleFavoritesExport);
    webserver.on("/importfavorites", HTTP_POST, handleFavoritesImport);
    webserver.on("/api/stationlist", handleApiStationList);
    webserver.on("/restart", HTTP_POST, handleRestart);
    webserver.on("/log", HTTP_GET, handleLog);
    webserver.on("/favicon.ico", HTTP_GET, handleFavicon);
    webserver.on("/api/say", handleApiSay);
    webserver.on("/api/play", handleApiPlay);
    webserver.on("/api/station", handleApiStation);
    webserver.on("/api/stations", HTTP_GET, handleApiStations);
    webserver.on("/api/stationdelete", handleApiStationDelete);
    webserver.on("/api/favorites", handleApiFavorites);
    webserver.on("/api/favoriteadd", handleApiFavoriteAdd);
    webserver.on("/api/favoritedelete", handleApiFavoriteDelete);
    webserver.on("/api/favoritestolist", handleApiFavoritesToList);
    webserver.on("/api/url", handleApiUrl);
    webserver.on("/api/file", handleApiFile);
    webserver.on("/api/log", handleApiLog);
    webserver.on("/api/stop", handleApiStop);
    webserver.on("/api/mute", handleApiMute);
    webserver.on("/api/volume", handleApiVolume);
    webserver.on("/api/status", HTTP_GET, handleApiStatus);
    webserver.on("/api/files", HTTP_GET, handleApiFiles);
    webserver.on("/api/sd", HTTP_GET, handleApiSd);
    webserver.on("/api/sdmount", handleApiSdMount);
    webserver.on("/api/ttscache", handleApiTtsCache);
    webserver.on("/api/effect", handleApiEffect);
    webserver.on("/panel", HTTP_GET, handlePanel);
    webserver.on("/api/sdmkdir", handleApiSdMkdir);
    webserver.on("/api/sddelete", handleApiSdDelete);
    webserver.on("/api/sdrename", handleApiSdRename);
    webserver.on("/api/sdfile", HTTP_GET, handleApiSdFile);
    webserver.on("/api/fileget", HTTP_GET, handleApiFileGet);
    webserver.on("/api/flash", HTTP_GET, handleApiFlash);
    webserver.on("/api/delete", handleApiDelete);
    webserver.on("/api/rename", handleApiRename);
    webserver.on("/api/scan", HTTP_GET, handleApiScan);
    webserver.on("/api/scanwifi", HTTP_GET, handleApiScanWifi);
    webserver.on("/api/rescanwifi", HTTP_POST, handleApiRescanWifi);
    webserver.on("/sethostname", HTTP_POST, handleSetHostname);
    webserver.on("/deletewifi", HTTP_GET, handleDeleteWifi);
    webserver.on("/api/connectWifi", HTTP_GET, handleConnectWifi);
    webserver.on("/api/testNtp", HTTP_GET, handleTestNtp);
    webserver.on("/api/mqtt", handleApiMqtt);
    webserver.on("/api/topbarStatus", HTTP_GET, handleTopbarStatus);
    webserver.on("/api/version", HTTP_GET, handleVersion);
    webserver.on("/upload", HTTP_POST, handleUploadDone, handleUploadData);
    webserver.on("/lang.json", HTTP_GET, handleLangJson);
    webserver.on("/api/lang", handleApiLang);
    webserver.on("/api/pins", handleApiPins);
    webserver.onNotFound([]() { webserver.send(404, "text/plain", "Not found"); });
    webserver.begin();
    logLine("[WEB] server started");
}
