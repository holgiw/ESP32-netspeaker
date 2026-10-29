# Changelog

## 2026-10-29 - Version 1.1.0

**Deutsch**

- Ordner der SD-Karte spielen mit `shuffle=1` in zufälliger Reihenfolge: jede Datei einmal je Sitzung, die Reihenfolge ist jedes Mal eine andere und beginnt nie mit der Datei der letzten Sitzung dieses Ordners. `loop=1` (Häkchen *Endlos*) startet danach eine neue, neu gemischte Runde ohne die zuletzt gespielte Datei am Anfang. Knopf *Zufall* im Tab *SD-Karte*, Parameter in REST und MQTT (JSON).
- Ordner werden jetzt einzeln nachgeladen statt auf einmal in die Warteschlange gelegt: es gibt keine Grenze von 8 Dateien mehr.
- Ansagen und Dateien werden nie mehr ein- oder ausgeblendet, auch nicht ohne Radio; nur das Radio blendet weiterhin aus, ein und wird abgesenkt.

**English**

- Folders of the SD card play in random order with `shuffle=1`: every file once per session, the order is different every time and never starts with the file the last session of this folder started with. `loop=1` (checkbox *Endlos*) then starts a new, reshuffled round without the file played last at the start. Button *Zufall* in the *SD-Karte* tab, parameters in REST and MQTT (JSON).
- Folders are now fed in one file at a time instead of all at once into the queue: the limit of 8 files is gone.
- Announcements and files are never faded in or out any more, not even without radio; only the radio still fades out, fades in and is ducked.

## 2026-10-28 - Version 1.0.0

**Deutsch**

- Erste Veröffentlichung als **NetSpeaker**: Netzwerk-Lautsprecher für den ESP32-S3 (4 MB Flash, 2 MB PSRAM) mit MAX98357A.
- Ansagen per VoiceRSS, Webradio, MP3-Dateien im Gerät und von der optionalen SD-Karte (mit Dateimanager; noch nicht produktiv getestet).
- Ansagen und Dateien laufen in einer Warteschlange; mit Webradio werden sie über das abgesenkte Radio gemischt, ohne Radio ein- und ausgeblendet.
- Lautstärke 0-100 mit sanften Änderungen, Titelregel mit mehreren Stichworten, Autostart und Wiederherstellen des letzten Zustands.
- Weboberfläche (Tabs Sprechen, Webradio, SD-Karte, MP3, Audio, MQTT, WLAN, Zeit, Status, Log, Doku) mit ``-Hinweisen und Verkabelungsplan, HTTP-API und MQTT.
- Export und Import der Einstellungen ohne WLAN-Passwörter und ohne API-Schlüssel; die Exportdatei trägt den Hostnamen im Namen.
- Platz 1 der Senderliste wird mit *RSA* vorbelegt, solange er leer ist.
- Lizenz GPL-3.0, Drittkomponenten in der README.

**English**

- First release as **NetSpeaker**: network speaker for the ESP32-S3 (4 MB flash, 2 MB PSRAM) with MAX98357A.
- Announcements via VoiceRSS, web radio, MP3 files in the device and from the optional SD card (with file manager; not tested in production yet).
- Announcements and files run in a queue; with web radio they are mixed over the ducked radio, without radio they fade in and out.
- Volume 0-100 with smooth changes, title rule with several keywords, autostart and restoring the last state.
- Web interface (tabs Sprechen, Webradio, SD-Karte, MP3, Audio, MQTT, WLAN, Zeit, Status, Log, Doku) with `` hints and wiring diagram, HTTP API and MQTT.
- Export and import of the settings without WiFi passwords and without API key; the export file carries the hostname in its name.
- Slot 1 of the station list is preset with *RSA* as long as it is empty.
- License GPL-3.0, third-party components in the README.