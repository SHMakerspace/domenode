EESchema Schematic File Version 4
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
L Connector:RJ45_Shielded J?
U 1 1 5B60B297
P 3450 850
F 0 "J?" V 3200 1350 50  0000 L CNN
F 1 "CAN_1" H 3350 1400 50  0000 L CNN
F 2 "" V 3450 875 50  0001 C CNN
F 3 "~" V 3450 875 50  0001 C CNN
	1    3450 850 
	0    1    1    0   
$EndComp
$Comp
L power:+24V #PWR?
U 1 1 5B60B47E
P 850 1700
F 0 "#PWR?" H 850 1550 50  0001 C CNN
F 1 "+24V" H 865 1873 50  0000 C CNN
F 2 "" H 850 1700 50  0001 C CNN
F 3 "" H 850 1700 50  0001 C CNN
	1    850  1700
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 5B60B4E3
P 850 700
F 0 "J?" V 816 512 50  0000 R CNN
F 1 "POWER_IN" V 950 800 50  0000 R CNN
F 2 "" H 850 700 50  0001 C CNN
F 3 "~" H 850 700 50  0001 C CNN
	1    850  700 
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B60B5B6
P 1000 950
F 0 "#PWR?" H 1000 700 50  0001 C CNN
F 1 "GND" H 1005 777 50  0000 C CNN
F 2 "" H 1000 950 50  0001 C CNN
F 3 "" H 1000 950 50  0001 C CNN
	1    1000 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  900  950  950 
Wire Wire Line
	950  950  1000 950 
Text Notes 2450 1150 0    50   ~ 0
1: VCC\n2: VCC\n3: VCC\n4: GND\n5: GND\n6: GND\n7: CAN+\n8: CAN-
Wire Wire Line
	3150 1250 3250 1250
Wire Wire Line
	3250 1250 3350 1250
Connection ~ 3250 1250
Wire Wire Line
	3450 1250 3550 1250
Wire Wire Line
	3650 1250 3550 1250
Connection ~ 3550 1250
Text GLabel 3250 1250 3    50   Input ~ 0
CANV
Text GLabel 3550 1250 3    50   Input ~ 0
CANGND
Text GLabel 3750 1250 3    50   Input ~ 0
CANH
Text GLabel 3850 1250 3    50   Input ~ 0
CANL
$Comp
L power:GND #PWR?
U 1 1 5B60B8B9
P 2950 900
F 0 "#PWR?" H 2950 650 50  0001 C CNN
F 1 "GND" H 2955 727 50  0000 C CNN
F 2 "" H 2950 900 50  0001 C CNN
F 3 "" H 2950 900 50  0001 C CNN
	1    2950 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 850  2950 900 
$Comp
L Diode:1N5819 D?
U 1 1 5B60B9F5
P 850 1550
F 0 "D?" V 896 1471 50  0000 R CNN
F 1 "1N5819" V 805 1471 50  0000 R CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 850 1375 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 850 1550 50  0001 C CNN
	1    850  1550
	0    -1   -1   0   
$EndComp
$Comp
L Device:Fuse F?
U 1 1 5B60BA80
P 850 1250
F 0 "F?" H 910 1296 50  0000 L CNN
F 1 "Fuse" H 910 1205 50  0000 L CNN
F 2 "" V 780 1250 50  0001 C CNN
F 3 "~" H 850 1250 50  0001 C CNN
	1    850  1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  900  850  1100
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5B60C018
P 1650 700
F 0 "J?" V 1616 512 50  0000 R CNN
F 1 "FAN_HEADER" V 1750 850 50  0000 R CNN
F 2 "" H 1650 700 50  0001 C CNN
F 3 "~" H 1650 700 50  0001 C CNN
	1    1650 700 
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B60C0E9
P 1750 900
F 0 "#PWR?" H 1750 650 50  0001 C CNN
F 1 "GND" H 1755 727 50  0000 C CNN
F 2 "" H 1750 900 50  0001 C CNN
F 3 "" H 1750 900 50  0001 C CNN
	1    1750 900 
	1    0    0    -1  
$EndComp
$Comp
L Connector:RJ45_Shielded J?
U 1 1 5B60C2F8
P 4650 850
F 0 "J?" V 4400 1350 50  0000 L CNN
F 1 "CAN_2" H 4550 1400 50  0000 L CNN
F 2 "" V 4650 875 50  0001 C CNN
F 3 "~" V 4650 875 50  0001 C CNN
	1    4650 850 
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 1250 4450 1250
Wire Wire Line
	4450 1250 4550 1250
Connection ~ 4450 1250
Wire Wire Line
	4650 1250 4750 1250
Wire Wire Line
	4850 1250 4750 1250
Connection ~ 4750 1250
Text GLabel 4450 1250 3    50   Input ~ 0
CANV
Text GLabel 4750 1250 3    50   Input ~ 0
CANGND
Text GLabel 4950 1250 3    50   Input ~ 0
CANH
Text GLabel 5050 1250 3    50   Input ~ 0
CANL
$Comp
L power:GND #PWR?
U 1 1 5B60C309
P 4150 900
F 0 "#PWR?" H 4150 650 50  0001 C CNN
F 1 "GND" H 4155 727 50  0000 C CNN
F 2 "" H 4150 900 50  0001 C CNN
F 3 "" H 4150 900 50  0001 C CNN
	1    4150 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 850  4150 900 
$Comp
L Connector:RJ45_Shielded J?
U 1 1 5B60C3A8
P 5850 850
F 0 "J?" V 5600 1350 50  0000 L CNN
F 1 "CAN_3" H 5750 1400 50  0000 L CNN
F 2 "" V 5850 875 50  0001 C CNN
F 3 "~" V 5850 875 50  0001 C CNN
	1    5850 850 
	0    1    1    0   
$EndComp
Wire Wire Line
	5550 1250 5650 1250
Wire Wire Line
	5650 1250 5750 1250
Connection ~ 5650 1250
Wire Wire Line
	5850 1250 5950 1250
Wire Wire Line
	6050 1250 5950 1250
Connection ~ 5950 1250
Text GLabel 5650 1250 3    50   Input ~ 0
CANV
Text GLabel 5950 1250 3    50   Input ~ 0
CANGND
Text GLabel 6150 1250 3    50   Input ~ 0
CANH
Text GLabel 6250 1250 3    50   Input ~ 0
CANL
$Comp
L power:GND #PWR?
U 1 1 5B60C3B9
P 5350 900
F 0 "#PWR?" H 5350 650 50  0001 C CNN
F 1 "GND" H 5355 727 50  0000 C CNN
F 2 "" H 5350 900 50  0001 C CNN
F 3 "" H 5350 900 50  0001 C CNN
	1    5350 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 850  5350 900 
$Comp
L Connector:RJ45_Shielded J?
U 1 1 5B60C64E
P 7050 850
F 0 "J?" V 6800 1350 50  0000 L CNN
F 1 "CAN_4" H 6950 1400 50  0000 L CNN
F 2 "" V 7050 875 50  0001 C CNN
F 3 "~" V 7050 875 50  0001 C CNN
	1    7050 850 
	0    1    1    0   
$EndComp
Wire Wire Line
	6750 1250 6850 1250
Wire Wire Line
	6850 1250 6950 1250
Connection ~ 6850 1250
Wire Wire Line
	7050 1250 7150 1250
Wire Wire Line
	7250 1250 7150 1250
Connection ~ 7150 1250
Text GLabel 6850 1250 3    50   Input ~ 0
CANV
Text GLabel 7150 1250 3    50   Input ~ 0
CANGND
Text GLabel 7350 1250 3    50   Input ~ 0
CANH
Text GLabel 7450 1250 3    50   Input ~ 0
CANL
$Comp
L power:GND #PWR?
U 1 1 5B60C65F
P 6550 900
F 0 "#PWR?" H 6550 650 50  0001 C CNN
F 1 "GND" H 6555 727 50  0000 C CNN
F 2 "" H 6550 900 50  0001 C CNN
F 3 "" H 6550 900 50  0001 C CNN
	1    6550 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 850  6550 900 
$Comp
L Connector:RJ45_Shielded J?
U 1 1 5B60C86F
P 3850 2450
F 0 "J?" V 3600 2950 50  0000 L CNN
F 1 "CAN_PI" H 3750 3000 50  0000 L CNN
F 2 "" V 3850 2475 50  0001 C CNN
F 3 "~" V 3850 2475 50  0001 C CNN
	1    3850 2450
	0    -1   -1   0   
$EndComp
Text GLabel 4050 2050 1    50   Input ~ 0
CANV
Text GLabel 3750 2050 1    50   Input ~ 0
CANGND
Text GLabel 3550 2050 1    50   Input ~ 0
CANH
Text GLabel 3450 2050 1    50   Input ~ 0
CANL
$Comp
L power:GND #PWR?
U 1 1 5B60C880
P 4350 2450
F 0 "#PWR?" H 4350 2200 50  0001 C CNN
F 1 "GND" H 4355 2277 50  0000 C CNN
F 2 "" H 4350 2450 50  0001 C CNN
F 3 "" H 4350 2450 50  0001 C CNN
	1    4350 2450
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_A J?
U 1 1 5B60CFE8
P 2800 2450
F 0 "J?" H 2600 2250 50  0000 R CNN
F 1 "PI_POWER" V 2550 2750 50  0000 R CNN
F 2 "" H 2950 2400 50  0001 C CNN
F 3 " ~" H 2950 2400 50  0001 C CNN
	1    2800 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 2050 2800 2050
Wire Wire Line
	3650 2050 3750 2050
Wire Wire Line
	3850 2050 3750 2050
Connection ~ 3750 2050
Wire Wire Line
	3950 2050 4050 2050
Wire Wire Line
	4150 2050 4050 2050
Connection ~ 4050 2050
Text GLabel 1500 1450 2    50   Input ~ 0
CANV
Text GLabel 1500 1550 2    50   Input ~ 0
CANGND
$Comp
L power:+24V #PWR?
U 1 1 5B60ECBB
P 1450 1450
F 0 "#PWR?" H 1450 1300 50  0001 C CNN
F 1 "+24V" H 1465 1623 50  0000 C CNN
F 2 "" H 1450 1450 50  0001 C CNN
F 3 "" H 1450 1450 50  0001 C CNN
	1    1450 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B60ED16
P 1450 1550
F 0 "#PWR?" H 1450 1300 50  0001 C CNN
F 1 "GND" H 1455 1377 50  0000 C CNN
F 2 "" H 1450 1550 50  0001 C CNN
F 3 "" H 1450 1550 50  0001 C CNN
	1    1450 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1450 1450 1450
Wire Wire Line
	1450 1550 1500 1550
$Comp
L mini-360:MINI-360 U?
U 1 1 5B60FBCE
P 1750 2350
F 0 "U?" H 1750 2625 50  0000 C CNN
F 1 "MINI-360" H 1750 2534 50  0000 C CNN
F 2 "" H 1750 2350 50  0001 C CNN
F 3 "" H 1750 2350 50  0001 C CNN
	1    1750 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR?
U 1 1 5B60FD6B
P 1400 2300
F 0 "#PWR?" H 1400 2150 50  0001 C CNN
F 1 "+24V" H 1415 2473 50  0000 C CNN
F 2 "" H 1400 2300 50  0001 C CNN
F 3 "" H 1400 2300 50  0001 C CNN
	1    1400 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B60FDA2
P 1400 2450
F 0 "#PWR?" H 1400 2200 50  0001 C CNN
F 1 "GND" H 1405 2277 50  0000 C CNN
F 2 "" H 1400 2450 50  0001 C CNN
F 3 "" H 1400 2450 50  0001 C CNN
	1    1400 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5B60FDE8
P 2100 2300
F 0 "#PWR?" H 2100 2150 50  0001 C CNN
F 1 "+5V" H 2115 2473 50  0000 C CNN
F 2 "" H 2100 2300 50  0001 C CNN
F 3 "" H 2100 2300 50  0001 C CNN
	1    2100 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B60FE10
P 2100 2450
F 0 "#PWR?" H 2100 2200 50  0001 C CNN
F 1 "GND" H 2105 2277 50  0000 C CNN
F 2 "" H 2100 2450 50  0001 C CNN
F 3 "" H 2100 2450 50  0001 C CNN
	1    2100 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5B60FE31
P 2350 2650
F 0 "#PWR?" H 2350 2500 50  0001 C CNN
F 1 "+5V" H 2365 2823 50  0000 C CNN
F 2 "" H 2350 2650 50  0001 C CNN
F 3 "" H 2350 2650 50  0001 C CNN
	1    2350 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2650 2500 2650
$Comp
L power:GND #PWR?
U 1 1 5B61033F
P 3200 2050
F 0 "#PWR?" H 3200 1800 50  0001 C CNN
F 1 "GND" H 3205 1877 50  0000 C CNN
F 2 "" H 3200 2050 50  0001 C CNN
F 3 "" H 3200 2050 50  0001 C CNN
	1    3200 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2050 2900 2050
Connection ~ 2900 2050
$Comp
L power:+5V #PWR?
U 1 1 5B610B3A
P 1600 900
F 0 "#PWR?" H 1600 750 50  0001 C CNN
F 1 "+5V" H 1615 1073 50  0000 C CNN
F 2 "" H 1600 900 50  0001 C CNN
F 3 "" H 1600 900 50  0001 C CNN
	1    1600 900 
	-1   0    0    1   
$EndComp
Wire Wire Line
	1650 900  1600 900 
$EndSCHEMATC
