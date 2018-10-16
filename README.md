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


# BoM and Components

## 1. Basic functionality and programming
* 1x ESP32 module
* 1x SOT-223 3v3 LDO regulator
* 2x 0603 10uF ceramic capacitors (decoupling)
* 2x 100uF tantalum capacitors (decoupling)
* 1x 4 pin ISP header
* 1x 2 pin SW0 flashing header
* 2x 0805 LED (power and blink)
* 2x 0603 resistors for LEDs (470 and 1k)
* 1x 0603 10k resistor EN (very much needed, R10)

## 2. NeoPixels
* 9x WS2812 LEDs
* 1x 0603 470 ohm resistor (R13)
* 9x 0603 100nF ceramic capacitors

## 3. External Power
* 1x MINI-360 buck regulator module (U1)
* 1x 1N5819 protection diode
* 1x 1210 10uF >24v capacitor (C1)
* 2x 0603 10uF ceramic capacitors (C2, C4 decoupling)
* 2x RJ45 connectors

## 4. CAN Bus
* 1x SN65HVD230DR transceiver IC (U6)
* 1x 2 pin CANTERM header
* 1x 0603 120 ohm resistor (R16)
* 1x 0603 10k resistor (R17)
* 1x 0603 100nF capacitor (C14, decoupling)


# Serial Programming
Order is:
Black, Green, White, Red 
(GND), (Rx), (Tx), (5V)

#Flashing Procedure
* 1. Determine COM port with command `mode`
* 2. Open terminal in esp32 python environment
* 3. esptool --chip esp32 -p COM<x> write_flash -z 0x1000 <firmware_bin>

Uploading files

ampy -p COM<x> put <file>