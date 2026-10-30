# Sprachdateien / Language files

**Deutsch**

Die Weboberfläche ist deutsch. Weitere Sprachen laden sich als Datei in den Speicher des Geräts und werden im Browser angewendet; sie kosten keinen Platz in der Firmware. `en.json` ist die englische Übersetzung.

- **Installieren:** Im Tab *Status* in der Karte *Sprache / Language* entweder **Von GitHub laden** (das Gerät holt die Datei mit dem eingetragenen Sprachcode, zum Beispiel `en`, aus dem Ordner `lang/` des Projekts; es braucht Internet) oder die Datei wählen und hochladen, oder per `curl -F "file=@en.json" "http://<ip>/upload?target=lang"`. Danach erscheint in der Statuszeile ein Knopf (EN/DE) zum Umschalten. Die Wahl wird im Browser gemerkt.
- **Aufbau:** `t` ordnet jedem deutschen Text (wie er in der Seite steht, Leerraum zusammengefasst) die Übersetzung zu. `r` sind Regeln für Texte mit wechselnden Werten: ein regulärer Ausdruck und der Ersatz mit `$1`, `$2` …. `{host}` steht für den Hostnamen des Geräts. Ein `\n` in einer Übersetzung ergibt in den Hinweisen (ⓘ) eine neue Zeile.
- **Neue Sprache:** `en.json` kopieren, zum Beispiel nach `fr.json` (zwei bis acht Kleinbuchstaben), die Werte übersetzen und hochladen.
- **Fehlende Übersetzungen finden:** `untranslated.js` in der Konsole des Browsers (F12) ausführen. Mit der Sprache DE listet es alle Schlüssel auf, mit der Sprache EN bleiben nur die Texte übrig, die noch nicht übersetzt sind (dazu zählen auch Dateinamen und andere Daten, die keine Übersetzung brauchen).
- Log, Fehlermeldungen im Protokoll und MQTT-Texte sind nicht Teil der Sprachdateien.

**English**

The web interface is in German. Further languages are loaded as a file into the memory of the device and applied in the browser; they cost no space in the firmware. `en.json` is the English translation.

- **Install:** In the *Status* tab, in the card *Sprache / Language*, either use **Von GitHub laden** (the device fetches the file with the entered language code, for example `en`, from the `lang/` folder of the project; it needs internet) or choose the file and upload it, or use `curl -F "file=@en.json" "http://<ip>/upload?target=lang"`. A button (EN/DE) then appears in the status bar to switch. The choice is remembered in the browser.
- **Structure:** `t` maps every German text (as it appears in the page, whitespace collapsed) to its translation. `r` are rules for texts with changing values: a regular expression and the replacement with `$1`, `$2` …. `{host}` stands for the hostname of the device. A `\n` in a translation gives a new line in the hints (ⓘ).
- **New language:** copy `en.json`, for example to `fr.json` (two to eight lowercase letters), translate the values and upload it.
- **Finding missing translations:** run `untranslated.js` in the console of the browser (F12). With the language set to DE it lists all keys; with EN only the texts that are not translated yet remain (including file names and other data that need no translation).
- Log, error messages in the log and MQTT texts are not part of the language files.
