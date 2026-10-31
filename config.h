#pragma once

// Projektkonfiguration: Namen, Standardwerte, erlaubte Pins.
// Project configuration: names, defaults, allowed pins.

#define PROJECT_NAME "netspeaker"

// Namespace der gespeicherten Einstellungen (NVS); bleibt unveraendert, damit bestehende Geraete ihre Einstellungen behalten.
// Namespace of the stored settings (NVS); stays unchanged so existing devices keep their settings.

#define PROJECT_NVS "voicerss"

#define PROJECT_TITLE "NetSpeaker"
#define PROJECT_TAG "SPEAKER"

// Der Text steht im Binary; checkDevices.ps1 liest ihn als Soll-Stand der .bin.
// The text is stored in the binary; checkDevices.ps1 reads it as the target state of the .bin.

#define FIRMWARE_MARKER "VOICE_FW_BUILD=" __DATE__ " " __TIME__
#define FIRMWARE_MARKER_PREFIX_LEN 15

// Standard-Pins fuer den MAX98357A am ESP32-S3; im Audio-Tab aenderbar (wirkt nach Neustart).
// Default pins for the MAX98357A on the ESP32-S3; changeable in the Audio tab (applies after restart).

#define DEFAULT_PIN_BCLK 3
#define DEFAULT_PIN_LRC 4
#define DEFAULT_PIN_DIN 2

// SD-Karte (SPI): Standard-Pins des Moduls am ESP32-S3; im Audio-Tab aenderbar. SD_LIST_MAX Eintraege pro Ordner werden angezeigt.
// SD card (SPI): default pins of the module on the ESP32-S3; changeable in the Audio tab. SD_LIST_MAX entries per folder are shown.

// Vorbelegter Sender auf Platz 1; gilt, solange Platz 1 leer ist (neues Geraet oder geloeschter Platz).
// Preset station in slot 1; applies as long as slot 1 is empty (new device or deleted slot).

#define DEFAULT_STATION_NAME "RSA"
#define DEFAULT_STATION_URL "https://rsa.streamabc.net/regc-rsalive-mp3-192-5989815"

#define DEFAULT_SD_CS 13
#define DEFAULT_SD_SCK 11
#define DEFAULT_SD_MOSI 12
#define DEFAULT_SD_MISO 10
#define SD_LIST_MAX 200

// Zeitgrenzen in Millisekunden bzw. Sekunden.
// Time limits in milliseconds and seconds respectively.

#define WDT_TIMEOUT_S 30
#define WIFI_CONNECT_TIMEOUT_MS 12000UL
#define WIFI_ATTEMPT_TIMEOUT_MS 10000UL
#define WIFI_FIRST_RETRY_MS 6000UL
#define WIFI_BACKOFF_START_MS 2000UL
#define WIFI_BACKOFF_MAX_MS 15000UL
#define WIFI_RESTART_AFTER_MS 600000UL
#define MQTT_BACKOFF_START_MS 1000UL
#define MQTT_BACKOFF_MAX_MS 10000UL
#define MQTT_BACKOFF_PLAYING_MS 8000UL
#define MQTT_TCP_TIMEOUT_MS 800
#define MQTT_KEEPALIVE_S 15
#define TTS_HTTP_TIMEOUT_MS 8000
#define TTS_DEADLINE_MS 25000UL
#define TTS_MAX_BYTES 400000UL
#define LOAD_TIMEOUT_MS 60000UL
#define SERIAL_PROVISION_WINDOW_MS 8000UL

// Selbstschutz: bei dauerhaft knappem Speicher neu starten; nach wiederholten Abstuerzen im Sicherheitsmodus starten.
// Self protection: restart if memory stays low; start in safe mode after repeated crashes.

#define HEAP_LOW_BYTES 15000
#define HEAP_LOW_RESTART_MS 60000UL
#define CRASH_LIMIT 3
#define STABLE_BOOT_MS 120000UL

// Radio: Wiederholungsabstaende beim automatischen Neuverbinden eines abgerissenen Live-Streams.
// Radio: retry delays when automatically reconnecting a dropped live stream.

#define RADIO_RETRY_START_MS 3000UL
#define RADIO_RETRY_MAX_MS 30000UL
#define RADIO_STABLE_MS 20000UL

// Kommt nach dem Start oder nach "Stream lost" so lange weder Ton (Dekoder bereit) noch irgendein neues Datenstueck an, wird der
// Stream selbst neu verbunden. Nach jedem erfolglosen Versuch verdoppelt sich die Wartezeit bis STREAM_READY_TIMEOUT_MAX_MS.
// If neither sound (decoder ready) nor any new chunk of data arrives for this long after the start or after "Stream lost", the
// stream is reconnected by the device itself. After each unsuccessful attempt the wait doubles up to STREAM_READY_TIMEOUT_MAX_MS.

#define STREAM_READY_TIMEOUT_MS 20000UL
#define STREAM_READY_TIMEOUT_MAX_MS 90000UL

// Autostart: Sender 1 nach dem Start abspielen, sobald das WLAN steht und der Stream antwortet.
// Autostart: play station 1 after the boot as soon as the WiFi is up and the stream answers.

#define AUTOSTART_DELAY_MS 2000UL
#define AUTOSTART_RETRY_MS 6000UL
#define AUTOSTART_MAX_TRIES 10

// Mischer: Ansagen und MP3-Dateien ueber ein laufendes Webradio legen (Puffergroessen und Vorlauf).
// Mixer: lay announcements and MP3 files over a running web radio (buffer sizes and lead).

#define MIX_IN_BYTES 6144
#define MIX_REFILL_BELOW 2560
#define MIX_PREFILL_FRAMES 3000

// Warteschlange fuer Ansagen und MP3-Dateien: so viele Eintraege koennen warten.
// Queue for announcements and MP3 files: this many entries can wait.

#define ANN_QUEUE_LEN 8

// Grenzen fuer Sprachtext und Logdatei.
// Limits for the speech text and the log file.

#define TTS_MAX_CHARS 500
#define LOG_MAX_BYTES 16384

// Dateien im LittleFS.
// Files in LittleFS.

#define MP3_DIR "/mp3"
#define TTS_FILE "/tts.mp3"
#define LOG_FILE "/log.txt"
#define LOG_OLD_FILE "/log.old"

// Lautstaerke: 0 bis 100 (die Audio-Bibliothek teilt ihre Kurve in genau so viele Stufen).
// Volume: 0 to 100 (the audio library divides its curve into exactly that many steps).

#define VOLUME_MAX 100

// Gespeicherte Webradio-/MP3-URLs: Anzahl der Plaetze und Laengen.
// Stored web radio / MP3 URLs: number of slots and lengths.

// Standarddauer des Ausblendens eines Webradios vor einer Ansage oder Datei (ms) und Obergrenze.
// Default duration of fading out a web radio before an announcement or file (ms) and its upper limit.

#define FADE_DEFAULT_MS 1200
#define FADE_MAX_MS 3000

// Standarddauer des Aus- und Einblendens bei einem Senderwechsel (ms).
// Default duration of fading out and in when the station is changed (ms).

#define SWITCH_FADE_DEFAULT_MS 1500

// Standarddauer, in der eine geaenderte Lautstaerke (Regler, REST, MQTT, Titelregel) bei laufendem Ton sanft zum neuen Wert wandert (ms), und Obergrenze.
// Default time in which a changed volume (slider, REST, MQTT, title rule) moves gently to the new value while sound is playing (ms), and the upper limit.

#define VOLUME_RAMP_DEFAULT_MS 1500
#define VOLUME_RAMP_MAX_MS 10000

// Zusaetzliche Feinteilung der internen Stufen der Audio-Bibliothek (Stufen = VOLUME_MAX mal VOL_FINE); 1 = keine.
// Additional fine division of the internal steps of the audio library (steps = VOLUME_MAX times VOL_FINE); 1 = none.

#define VOL_FINE 1

#define RADIO_SLOTS 30
#define RADIO_NAME_MAX 24

// Dieser Sender steht nach dem Laden einer Senderliste immer auf Platz 1.
// This station is always at slot 1 after a station list is loaded.

#define RSA_URL "https://rsa.streamabc.net/regc-rsalive-mp3-192-5989815"
#define RADIO_URL_MAX 200
