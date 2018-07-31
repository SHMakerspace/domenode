# domenode
A CAN bus controlled, WiFi enabled network of dome node LEDs with many features

# Features
* :heavy_check_mark: ESP32 microcontroller (WiFi, bluetooth)
  * Pads for both ESP32 standalone module and dev board variants
  * OTA wireless firmware updates
* :heavy_check_mark: SN65HVD230 CAN bus transceiver
* :heavy_check_mark: 2x RJ45 connectors for CAN in and passthrough
* :heavy_check_mark: 5x WS2812/NeoPixel for RGB lighting
* :heavy_check_mark: On-board buck regulator
* :heavy_check_mark: 2x push switches
* :heavy_check_mark: Power and GPIO LED
* :heavy_check_mark: many headers for sensors and attachments (I2C, GPIOs, power etc)
* :red_circle: A shield header for expansion boards (to be added)


# Sensors (all optional and do not need to be populated)
Optional features by means of populating those pads are:
* :question: Outer and inner facing LDRs for ambient/transmitted light sensing
* :question: 2x tactile push switches for on-board input
* :question: Heavier duty power RGB LED shield connector (exposes 24V and R,G,B GPIOs)
* :question: IR Tx/Rx and (hopefully!) a ghetto distance sensor
* :question: Speaker
* :question: Capacitive touch
* :question: Microphone - MAX4466 based breakout board connector (footprints could be added to board, alternative idea is I2S)

# Firmware notes
* CAN bus - http://www.barth-dev.de/can-driver-esp32/
* NeoPixels - https://www.instructables.com/id/ESP32-Bluetooth-Ambience-Light-Controller-With-WS2/
* Microphone -https://www.hackster.io/julianfschroeter/esp32-voice-streamer-52bd7e , https://github.com/MrBuddyCasino/ESP32_Alexa
* Speaker - http://www.xtronical.com/basics/audio/dacs-on-esp32/
* IR sensor - https://github.com/mdhiggins/ESP8266-HTTP-IR-Blaster
* I2C bus - https://randomnerdtutorials.com/esp32-with-bmp180-barometric-sensor/