# Integration / Integration

## Deutsch

Das Gerät wird über MQTT gesteuert; das Basis-Topic ist standardmäßig `netspeaker/<Hostname>` (im Tab *MQTT* änderbar). In den Beispielen steht `netspeaker/netspeaker-az`, bitte anpassen.

- **Home Assistant:** Im Tab *MQTT* den Haken *Home Assistant Discovery* setzen. Das Gerät meldet sich dann selbst an (Status, Läuft gerade, Lautstärke, Ansage, Stopp, Sender). Voraussetzung ist die MQTT-Integration von Home Assistant am selben Broker.
- **Node-RED:** `node-red-flow.json` über *Import* einlesen. Der Flow enthält Knöpfe für Ansage, Flash-MP3, Sender, Lautstärke, Stopp und das Gruppen-Topic `netspeaker/all/stop` sowie einen Empfänger für Status und Titel. Broker-Knoten und Topics anpassen.
- **openHAB:** `openhab/netspeaker.things` und `openhab/netspeaker.items` nach `conf/things` und `conf/items` kopieren. Es wird das MQTT-Binding mit einem Broker-Thing `mosquitto` vorausgesetzt.

Alle Topics und Nutzlasten stehen in der README (Abschnitt MQTT) und im Tab *Doku* der Weboberfläche.

## English

The device is controlled via MQTT; the base topic is `netspeaker/<hostname>` by default (changeable in the *MQTT* tab). The examples use `netspeaker/netspeaker-az`, please adjust.

- **Home Assistant:** tick *Home Assistant Discovery* in the *MQTT* tab. The device then registers itself (status, now playing, volume, announcement, stop, station). The MQTT integration of Home Assistant on the same broker is required.
- **Node-RED:** import `node-red-flow.json`. The flow has buttons for announcement, flash MP3, station, volume, stop and the group topic `netspeaker/all/stop`, plus a receiver for status and title. Adjust the broker node and topics.
- **openHAB:** copy `openhab/netspeaker.things` and `openhab/netspeaker.items` to `conf/things` and `conf/items`. The MQTT binding with a broker thing `mosquitto` is required.

All topics and payloads are listed in the README (section MQTT) and in the *Doku* tab of the web interface.
