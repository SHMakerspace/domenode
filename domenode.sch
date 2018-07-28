EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:lpc11c22_lqfp48
LIBS:ESP32-footprints-Shem-Lib
LIBS:domenode-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP32-WROOM U?
U 1 1 5B5C3F6F
P 2400 3300
F 0 "U?" H 1700 4550 60  0000 C CNN
F 1 "ESP32-WROOM" H 2900 4550 60  0000 C CNN
F 2 "ESP32-footprints-Lib:ESP32-WROOM" H 2750 4650 60  0001 C CNN
F 3 "" H 1950 3750 60  0001 C CNN
	1    2400 3300
	1    0    0    -1  
$EndComp
Text Notes 7150 2200 0    60   ~ 0
1: VCC\n2: VCC\n3: VCC\n4: GND\n5: GND\n6: GND\n7: CAN+\n8: CAN-
$Comp
L RJ45 J?
U 1 1 5B5C4051
P 7350 2850
F 0 "J?" H 7550 3350 50  0000 C CNN
F 1 "RJ45" H 7200 3350 50  0000 C CNN
F 2 "" H 7350 2850 50  0001 C CNN
F 3 "" H 7350 2850 50  0001 C CNN
	1    7350 2850
	0    1    1    0   
$EndComp
$Comp
L RJ45 J?
U 1 1 5B5C408E
P 7350 3900
F 0 "J?" H 7550 4400 50  0000 C CNN
F 1 "RJ45" H 7200 4400 50  0000 C CNN
F 2 "" H 7350 3900 50  0001 C CNN
F 3 "" H 7350 3900 50  0001 C CNN
	1    7350 3900
	0    1    1    0   
$EndComp
$EndSCHEMATC
