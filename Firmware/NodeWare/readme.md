# DomeNode Firmware
The firmware for the DomeNodes is written in Arduino for the ESP32 microcontroller platform

## Dependencies
The required dependancies are included with this repository as submodules, except the ESP32 Arduino core toolchain which has to be installed manually.
* [Arduino core for ESP32 WiFi chip](https://github.com/espressif/arduino-esp32) - install via Arduino IDE boards manager
* [Arduino CAN](https://github.com/sandeepmistry/arduino-CAN) - included as submodule
* [NeoPixelBus](https://github.com/Makuna/NeoPixelBus) - included as submodule

## Compiling
To compile the firmware correctly for the DomeNode, please ensure your Arduino IDE has the following parameters set in the 'Tools' menu;
* Board: ESP32 Dev Module
* Flash mode: QIO
* Flash frequency: 40MHz
* Flash size: 4MB (32Mb)
* PSRAM: Disabled
* Partition scheme: Minimal SPIFFS (Large apps with OTA)
* Upload speed: 921600
* Core debug level: None

## Node IDs
To assign an ID to a node, simply set the `node_id` to your chosen ID and it will be persistantly stored. You only need this variable set once, you can remove it from future firmware uploads it it'll retrive the last set ID from flash memory.

## OTA updates
To update via OTA, first flash the firmware over serial, ensuring that you have changed the WiFi credentials to the same network your machine running the Arduino IDE is connected to.
When the DomeNode connects to your network, navigate to the 'Port' option under the 'Tools' in the Arduino IDE. You should your DomeNode appear under the serial ports.