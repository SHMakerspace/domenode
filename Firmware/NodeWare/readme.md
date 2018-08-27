# DomeNode Firmware
The firmware for the DomeNodes is written in Arduino for the ESP32 microcontroller platform

## Dependencies
* [Arduino core for ESP32 WiFi chip](https://github.com/espressif/arduino-esp32) - install via Arduino IDE boards manager
* [Arduino CAN](https://github.com/sandeepmistry/arduino-CAN) - install via Arduino IDE libraries manager
* [NeoPixelBus](https://github.com/Makuna/NeoPixelBus) - install via Arduino IDE libraries manage

### Node IDs
To assign an ID to a node, simply set the `node_id` to your chosen ID and it will be persistantly stored.