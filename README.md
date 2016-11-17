# Workshop:  IoT Experiments - build your own prototype!

## Description
This repository contains sources for IoT Experiments workshop.
The workshop is based on programming NodeMCU (ESP8266) with Arduino IDE.

Work is split to four parts (steps):
- device assembly
- work with temperature sensor
- HTTP calls
- connection to cloud - Yaas

## Requirements !!!
All steps have to be performed before workshop!

### Arduino

#### Install Arduino IDE
https://www.arduino.cc/en/Main/Software - choose your operating system in the menu on the right side, on next page click "Just download"

#### Add NodeMCU board

- run Arduino
- go to [File > Preferences](tools/screenshots/preferences.png?raw=true) and paste "http://arduino.esp8266.com/staging/package_esp8266com_index.json" into Additional Board Manager URLs", save changes
- go to Tools > Board > [Boards Manager](tools/screenshots/boards_manager.png?raw=true), search for ESP8266, click on it and Install  

#### Add libraries

Go to Sketch > Include Library > [Manage Libraries](tools/screenshots/library_manager.png?raw=true)
Search and install 3 packages (paste it exactly like it is):
 - "Adafruit Unified Sensor based libraries"
 - "DHT sensor library"
 - "ArduinoJson"

#### USB drivers
 - OSX: [Install driver](tools/drivers/osx/osx-vcp-driver.zip?raw=true)
 - Windows: driver is build in

### Yaas

1. Create Yaas account - https://www.yaas.io/register/ - use the same email address that you used in workshop registration form
2. Before workshop we'll send you invitation to join our IoT Workshop Project