# Changelog

## 2026-10-29 - Version 1.3.0

**Deutsch**

- Die Weboberfläche lässt sich in weiteren Sprachen anzeigen. Eine Sprachdatei (`lang/en.json` für Englisch) wird im Tab *Status* in der Karte *Sprache / Language* hochgeladen, liegt im Speicher des Geräts und wird im Browser angewendet; in der Statuszeile wechselt ein Knopf (EN/DE) die Sprache. Die Firmware wird dafür nur um wenige KB größer, die Übersetzung selbst braucht keinen Platz in der App-Partition. Anleitung und Prüfwerkzeug für fehlende Übersetzungen: `lang/README.md`.
- Nicht eingestellte Pins (alle zugelassenen außer Verstärker, SD-Karte, Strapping-Pins und Status-LED) bekommen einen Pull-up (High), damit offene Pins nicht schweben.
- Neuer Tab *Eingänge*: Je freiem Pin lässt sich eine Aktion festlegen; bei einer MP3-Datei bietet eine Auswahl die Dateien im Flash und auf der SD-Karte an. Bekommt der Pin Kontakt nach GND (zum Beispiel durch eine Taste), spielt das Gerät eine Ansage (VoiceRSS) oder eine MP3-Datei, einen Ordner der SD-Karte oder eine URL. REST: `/api/pins`.
- Der Fortschrittsbalken unter dem Namen wird bei Webradio ausgeblendet, weil ein Stream keine Länge hat.
- Im Tab *Sprechen* steht neben dem Lautstärkeregler der Wert (zum Beispiel 60 / 100); er folgt dem Regler und der tatsächlichen Lautstärke.
- Tab *Status*: Die SD-Karte zeigt jetzt Zustand, Größe, belegt (mit Prozent), frei, ob sie eingeschaltet ist und die vier Pins (CS, SCK, MOSI, MISO).

**English**

- The web interface can be shown in further languages. A language file (`lang/en.json` for English) is uploaded in the *Status* tab, in the card *Sprache / Language*, is stored in the memory of the device and applied in the browser; a button (EN/DE) in the status bar switches the language. The firmware only grows by a few KB, the translation itself needs no space in the app partition. Instructions and a tool for finding missing translations: `lang/README.md`.
- Pins that are not configured (all allowed ones except amplifier, SD card, strapping pins and status LED) get a pull-up (high) so that open pins do not float.
- New tab *Eingänge*: an action can be set per free pin; for an MP3 file a list offers the files in flash and on the SD card. When the pin gets contact to GND (for example through a button), the device plays an announcement (VoiceRSS) or an MP3 file, a folder of the SD card or a URL. REST: `/api/pins`.
- The progress bar under the name is hidden for web radio, because a stream has no length.
- In the *Sprechen* tab the value is shown next to the volume slider (for example 60 / 100); it follows the slider and the actual volume.
- *Status* tab: the SD card now shows state, size, used (with percent), free, whether it is enabled and the four pins (CS, SCK, MOSI, MISO).

## 2026-10-29 - Version 1.2.1

**Deutsch**

- Der Titel eines Webradios wird erst angezeigt (und für die Titelregel gemeldet), wenn die dazu gehörende Musik zu hören ist: Er wird um die Dauer des gepufferten Tons verzögert. Im Log steht bei jedem neuen Titel die Verzögerung (`[TITLE] ... shown in ... ms`).
- Titelregel: Mit *höchstens … s* im Tab *Audio* endet die angehobene Lautstärke nach einer festen Zeit (zum Beispiel 210 s), weil ein Sender das Ende eines Titels nicht meldet und Werbung danach sonst laut bleibt. 0 = bis zum nächsten Titel (Standard).
- Der Tab *MP3* heißt jetzt *MP3 (Flash)*, zur Abgrenzung von der SD-Karte. In der Statuszeile steht als Marke jetzt *SPEAKER* statt *VOICE*.
- *Stream-Info* zeigt zusätzlich Codec, Abtastrate und Kanäle; sie stehen auch im Status als `codec`, `rate`, `ch` und `bits`.
- Kurzer Ton („buub“) beim Start in der eingestellten Lautstärke; nach einem Neustart per MQTT, nach eigenen Neustarts des Geräts (WLAN lange weg, Speicher knapp), nach einem Absturz und im abgesicherten Modus bleibt er aus. Haken *Kurzer Ton beim Start* im Tab *Audio* (Standard: an).

**English**

- The title of a web radio is only shown (and passed to the title rule) when the matching music is audible: it is delayed by the duration of the buffered sound. The log shows the delay for every new title (`[TITLE] ... shown in ... ms`).
- Title rule: with *höchstens … s* in the *Audio* tab the raised volume ends after a fixed time (for example 210 s), because a station does not report the end of a title and ads after it would otherwise stay loud. 0 = until the next title (default).
- The tab *MP3* is now called *MP3 (Flash)*, to tell it apart from the SD card. The brand in the status bar is now *SPEAKER* instead of *VOICE*.
- *Stream-Info* additionally shows codec, sample rate and channels; they are also in the status as `codec`, `rate`, `ch` and `bits`.
- Short tone ("buub") at the start at the set volume; it stays off after a restart via MQTT, after restarts the device triggers itself (WiFi lost for long, low memory), after a crash and in safe mode. Checkbox *Kurzer Ton beim Start* in the *Audio* tab (default: on).

## 2026-10-29 - Version 1.2.0

**Deutsch**

- Eine Ansage stoppt eine laufende MP3-Datei (auch aus einem Ordner der SD-Karte) nicht mehr, sondern wird leise darübergemischt; die Datei läuft abgesenkt weiter. Voraussetzung ist der Haken *Radio unter Ansagen weiterlaufen lassen* im Tab *Audio*. Mehrere Ansagen laufen nacheinander und kommen vor den wartenden Dateien dran.
- Bei laufender MP3-Datei zeigt die Oberfläche unter dem Namen einen Fortschrittsbalken (Position und Länge in der Statusabfrage: `pos`, `dur` in Sekunden). Zufall und Ordner-Knopf gibt es nun auch im Hauptverzeichnis der SD-Karte.
- MP3-Dateien werden beim Start ein- und am Ende ausgeblendet (Dauer: *Radio aus-/einblenden*); Ansagen werden nie ein- oder ausgeblendet.
- MP3-Dateien werden in der Lautstärke angeglichen: Beim ersten Abspielen misst das Gerät im Hintergrund die Lautheit der Datei und speichert den Ausgleich (`/loudness.bin`); Ansagen und Radio bleiben unverändert. Haken *MP3-Lautstärke angleichen* im Tab *Audio* (Standard: an).
- Tab *Webradio*: aufklappbarer Bereich *Stream-Info* mit Sender, Titel, Genre, Beschreibung, Webseite, Logo-Adresse, Bitrate und Server, soweit der Sender sie liefert; die Werte stehen auch im Status.

**English**

- An announcement no longer stops a running MP3 file (including one from a folder of the SD card): it is mixed quietly over it and the file keeps playing, lowered. This needs the checkbox *Radio unter Ansagen weiterlaufen lassen* in the *Audio* tab. Several announcements play one after another and come before the waiting files.
- While an MP3 file plays, the web interface shows a progress bar under the name (position and length in the status query: `pos`, `dur` in seconds). Random and the folder button are now also available in the root of the SD card.
- MP3 files fade in at the start and out at the end (duration: *Radio aus-/einblenden*); announcements are never faded in or out.
- The volume of MP3 files is matched: on the first play the device measures the loudness of the file in the background and stores the correction (`/loudness.bin`); announcements and radio stay unchanged. Checkbox *MP3-Lautstärke angleichen* in the *Audio* tab (default: on).
- *Webradio* tab: collapsible *Stream-Info* area with station, title, genre, description, website, logo address, bitrate and server as far as the station delivers them; the values are also in the status.

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