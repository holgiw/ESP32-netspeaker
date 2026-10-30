NetSpeaker - Flash-Werkzeuge / flash tools
==========================================

Deutsch
-------
Dieser Ordner enthaelt die Werkzeuge zum Flashen eines NetSpeaker (ESP32-S3) per USB.

Nur flashen (ohne Arduino IDE, ohne das Repository):
  1. netspeaker_flash.zip aus dem neuesten Release laden:
     https://github.com/holgiw/ESP32-netspeaker/releases/latest
  2. Das Zip KOMPLETT in einen Ordner auspacken (esptool.exe muss neben flashESP.bat liegen).
  3. ESP32-S3 per USB anschliessen, flashESP.bat doppelklicken.
Das Skript sucht den ESP, laedt netspeaker-esp32s3.zip vom neuesten Release (Pruefsumme SHA-256, Internet noetig),
flasht ihn (die Einstellungen im Geraet bleiben erhalten) und fragt danach das WLAN ab: sichtbare 2,4-GHz-Netze,
das WLAN des PCs mit gespeichertem Passwort zum Uebernehmen, Eingabetaste = WLAN nicht aendern. Die Daten gehen per
USB an das Geraet. Danach: http://netspeaker-<xx>.local/ bzw. die IP-Adresse im Browser.

Mit eigenem Build (Entwicklung):
  buildAll.bat (im Projektordner) baut die Firmware und legt sie im Ordner esp32s3 hier ab; flashESP.bat nimmt dann
  diesen lokalen Build statt des Downloads. -Download erzwingt den Download (voicesetup.ps1 -Download).

Dateien
  flashESP.bat         Doppelklick: ESP suchen, flashen, WLAN abfragen. Mit Parameter ohne Rueckfragen: flashESP.bat 3 (COM3)
  voicesetup.ps1       das eigentliche Skript (wird von flashESP.bat und ../flashAll.bat aufgerufen)
  publish_builds.ps1   erzeugt die Pakete fuer das Release (netspeaker-esp32s3.zip, .sha256, netspeaker_flash.zip)
  esptool.exe          Flash-Werkzeug von Espressif (GPL-2.0, https://github.com/espressif/esptool); steht nur im Werkzeug-Zip.
                       Sonst wird das esptool aus dem ESP32-Core der Arduino IDE genommen.
Antivirus: Meldet der Virenscanner esptool.exe (Fehlalarm), eine Ausnahme fuer den Ordner einrichten.

English
-------
This folder holds the tools for flashing a NetSpeaker (ESP32-S3) via USB.

Flash only (no Arduino IDE, no repository):
  1. Download netspeaker_flash.zip from the newest release:
     https://github.com/holgiw/ESP32-netspeaker/releases/latest
  2. Unpack the WHOLE zip into a folder (esptool.exe has to be next to flashESP.bat).
  3. Connect the ESP32-S3 via USB and double-click flashESP.bat.
The script finds the ESP, downloads netspeaker-esp32s3.zip from the newest release (SHA-256 checked, internet needed),
flashes it (the settings in the device stay) and then asks for the WiFi: visible 2.4 GHz networks, the WiFi of the PC
with its stored password to take over, Enter = leave the WiFi unchanged. The data goes to the device via USB.
Afterwards open http://netspeaker-<xx>.local/ or the IP address in the browser.

With your own build (development):
  buildAll.bat (in the project folder) builds the firmware and puts it in the folder esp32s3 here; flashESP.bat then uses
  this local build instead of the download. -Download forces the download (voicesetup.ps1 -Download).

Files
  flashESP.bat         double-click: find the ESP, flash, ask for the WiFi. With a parameter without questions: flashESP.bat 3 (COM3)
  voicesetup.ps1       the actual script (called by flashESP.bat and ../flashAll.bat)
  publish_builds.ps1   creates the packages for the release (netspeaker-esp32s3.zip, .sha256, netspeaker_flash.zip)
  esptool.exe          flash tool by Espressif (GPL-2.0, https://github.com/espressif/esptool); only in the tools zip.
                       Otherwise the esptool of the ESP32 core of the Arduino IDE is used.
Antivirus: if the virus scanner reports esptool.exe (false alarm), add an exception for the folder.
