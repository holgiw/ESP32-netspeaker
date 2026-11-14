# Sprachen / Languages

**Deutsch**

Die Weboberfläche ist deutsch. `en.json` ist die englische Übersetzung; sie ist in die Firmware eingebaut: `makeLangHeader.ps1` (von `buildAll.bat` vor jedem Build aufgerufen) erzeugt daraus `lang_en_json.h`. Das Gerät liefert sie unter `/lang.json?l=en`, der Browser wendet sie an. Ein Knopf (EN/DE) in der Statuszeile schaltet um, die Wahl wird im Browser gemerkt. Hochladen oder Nachladen von Sprachdateien gibt es nicht mehr.

- **Aufbau:** `t` ordnet jedem deutschen Text (wie er in der Seite steht, Leerraum zusammengefasst) die Übersetzung zu. `r` sind Regeln für Texte mit wechselnden Werten: ein regulärer Ausdruck und der Ersatz mit `$1`, `$2` …. `{host}` steht für den Hostnamen des Geräts. Ein `\n` in einer Übersetzung ergibt in den Hinweisen (ⓘ) eine neue Zeile.
- **Ändern:** `en.json` bearbeiten und neu bauen (`buildAll.bat`), dann flashen.
- **Fehlende Übersetzungen finden:** `untranslated.js` in der Konsole des Browsers (F12) ausführen. Mit der Sprache DE listet es alle Schlüssel auf, mit der Sprache EN bleiben nur die Texte übrig, die noch nicht übersetzt sind (dazu zählen auch Dateinamen und andere Daten, die keine Übersetzung brauchen).
- Log, Fehlermeldungen im Protokoll und MQTT-Texte sind nicht Teil der Übersetzung.

**English**

The web interface is in German. `en.json` is the English translation; it is built into the firmware: `makeLangHeader.ps1` (called by `buildAll.bat` before every build) turns it into `lang_en_json.h`. The device delivers it at `/lang.json?l=en` and the browser applies it. A button (EN/DE) in the status bar switches, the choice is remembered in the browser. Uploading or loading language files no longer exists.

- **Structure:** `t` maps every German text (as it appears in the page, whitespace collapsed) to its translation. `r` are rules for texts with changing values: a regular expression and the replacement with `$1`, `$2` …. `{host}` stands for the hostname of the device. A `\n` in a translation gives a new line in the hints (ⓘ).
- **Changing:** edit `en.json` and rebuild (`buildAll.bat`), then flash.
- **Finding missing translations:** run `untranslated.js` in the console of the browser (F12). With the language set to DE it lists all keys; with EN only the texts that are not translated yet remain (including file names and other data that need no translation).
- Log, error messages in the log and MQTT texts are not part of the translation.
