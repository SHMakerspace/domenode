EESchema Schematic File Version 4
LIBS:domenode-cache
EELAYER 26 0
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
L ESP32-footprints-Shem-Lib:ESP32-WROOM U?
U 1 1 5B5C3F6F
P 3550 3300
F 0 "U?" H 2850 4550 60  0000 C CNN
F 1 "ESP32-WROOM" H 4050 4550 60  0000 C CNN
F 2 "ESP32-footprints-Lib:ESP32-WROOM" H 3900 4650 60  0001 C CNN
F 3 "" H 3100 3750 60  0001 C CNN
	1    3550 3300
	1    0    0    -1  
$EndComp
Text Notes 8100 3450 0    60   ~ 0
1: VCC\n2: VCC\n3: VCC\n4: GND\n5: GND\n6: GND\n7: CAN+\n8: CAN-
$Comp
L conn:RJ45 J?
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
L conn:RJ45 J?
U 1 1 5B5C408E
P 7350 3900
F 0 "J?" H 7550 4400 50  0000 C CNN
F 1 "RJ45" H 7200 4400 50  0000 C CNN
F 2 "" H 7350 3900 50  0001 C CNN
F 3 "" H 7350 3900 50  0001 C CNN
	1    7350 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	6900 2500 6900 2600
Connection ~ 6900 2600
Wire Wire Line
	6900 3550 6900 3650
Connection ~ 6900 3650
Wire Wire Line
	6900 3850 6900 3950
Connection ~ 6900 3950
Wire Wire Line
	6900 2800 6900 2900
Connection ~ 6900 2900
Text GLabel 6650 2600 0    60   Input ~ 0
CANV
Text GLabel 6650 3650 0    60   Input ~ 0
CANV
Text GLabel 6650 2900 0    60   Input ~ 0
CANGND
Text GLabel 6650 3950 0    60   Input ~ 0
CANGND
Wire Wire Line
	6900 3950 6650 3950
Wire Wire Line
	6900 3650 6650 3650
Wire Wire Line
	6900 2900 6650 2900
Wire Wire Line
	6900 2600 6650 2600
$Comp
L sn65hvd230:SN65HVD230 U?
U 1 1 5B5C480B
P 5450 3300
F 0 "U?" H 5450 3300 60  0000 C CNN
F 1 "SN65HVD230" H 5450 3300 60  0000 C CNN
F 2 "" H 5450 3300 60  0001 C CNN
F 3 "" H 5450 3300 60  0001 C CNN
	1    5450 3300
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5B5C4C1B
P 2400 2700
F 0 "#PWR?" H 2400 2550 50  0001 C CNN
F 1 "VCC" H 2400 2850 50  0000 C CNN
F 2 "" H 2400 2700 50  0001 C CNN
F 3 "" H 2400 2700 50  0001 C CNN
	1    2400 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2600 2700 2400 2700
$Comp
L power:GND #PWR?
U 1 1 5B5C4DCC
P 2600 4100
F 0 "#PWR?" H 2600 3850 50  0001 C CNN
F 1 "GND" H 2600 3950 50  0000 C CNN
F 2 "" H 2600 4100 50  0001 C CNN
F 3 "" H 2600 4100 50  0001 C CNN
	1    2600 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4000 2600 4100
Wire Wire Line
	6900 3100 6200 3100
Wire Wire Line
	5950 3100 5950 3200
Wire Wire Line
	5950 3450 6050 3450
Wire Wire Line
	6050 3200 6050 3450
Wire Wire Line
	6050 3200 6900 3200
Wire Wire Line
	6900 4150 6200 4150
Wire Wire Line
	6200 4150 6200 3100
Connection ~ 6200 3100
Wire Wire Line
	6050 4250 6900 4250
Connection ~ 6050 3450
Wire Wire Line
	4450 3350 4950 3350
Wire Wire Line
	4950 3350 4950 3200
Wire Wire Line
	4450 3650 4950 3650
Wire Wire Line
	4950 3650 4950 3450
$Comp
L conn:CONN_01X04 J?
U 1 1 5B5C8DEB
P 5250 2150
F 0 "J?" H 5250 2400 50  0000 C CNN
F 1 "SERIAL_ISP" V 5350 2150 50  0000 C CNN
F 2 "" H 5250 2150 50  0001 C CNN
F 3 "" H 5250 2150 50  0001 C CNN
	1    5250 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2750 4800 2750
Wire Wire Line
	4800 2750 4800 2100
Wire Wire Line
	4800 2100 5050 2100
Wire Wire Line
	5050 2200 4850 2200
Wire Wire Line
	4850 2200 4850 2850
Wire Wire Line
	4850 2850 4450 2850
$Comp
L power:VCC #PWR?
U 1 1 5B5C8E66
P 5050 1900
F 0 "#PWR?" H 5050 1750 50  0001 C CNN
F 1 "VCC" H 5050 2050 50  0000 C CNN
F 2 "" H 5050 1900 50  0001 C CNN
F 3 "" H 5050 1900 50  0001 C CNN
	1    5050 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 1900 5050 2000
$Comp
L power:GND #PWR?
U 1 1 5B5C8EDB
P 5050 2350
F 0 "#PWR?" H 5050 2100 50  0001 C CNN
F 1 "GND" H 5050 2200 50  0000 C CNN
F 2 "" H 5050 2350 50  0001 C CNN
F 3 "" H 5050 2350 50  0001 C CNN
	1    5050 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2300 5050 2350
Wire Wire Line
	6900 2600 6900 2700
Wire Wire Line
	6900 3650 6900 3750
Wire Wire Line
	6900 3950 6900 4050
Wire Wire Line
	6900 2900 6900 3000
Wire Wire Line
	6200 3100 5950 3100
Wire Wire Line
	6050 3450 6050 4250
$Comp
L LED:WS2812B D?
U 1 1 5B5C9AAA
P 4450 5450
F 0 "D?" H 4791 5496 50  0000 L CNN
F 1 "WS2812B" H 4791 5405 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 4500 5150 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 4550 5075 50  0001 L TNN
	1    4450 5450
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 5B5C9BBE
P 5350 5450
F 0 "D?" H 5691 5496 50  0000 L CNN
F 1 "WS2812B" H 5691 5405 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 5400 5150 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 5450 5075 50  0001 L TNN
	1    5350 5450
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 5B5C9BFA
P 6250 5450
F 0 "D?" H 6591 5496 50  0000 L CNN
F 1 "WS2812B" H 6591 5405 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 6300 5150 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 6350 5075 50  0001 L TNN
	1    6250 5450
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 5B5C9C38
P 7150 5450
F 0 "D?" H 7491 5496 50  0000 L CNN
F 1 "WS2812B" H 7491 5405 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 7200 5150 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 7250 5075 50  0001 L TNN
	1    7150 5450
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 5B5C9C70
P 8050 5450
F 0 "D?" H 8391 5496 50  0000 L CNN
F 1 "WS2812B" H 8391 5405 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 8100 5150 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 8150 5075 50  0001 L TNN
	1    8050 5450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
