EESchema Schematic File Version 4
EELAYER 30 0
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
L Regulator_Linear:LM1085-ADJ U2
U 1 1 609609F4
P 2600 900
F 0 "U2" H 2600 1142 50  0000 C CNN
F 1 "LM1085-ADJ" H 2600 1051 50  0000 C CNN
F 2 "digikey-footprints:TO-220-3" H 2600 1150 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm1085.pdf" H 2600 900 50  0001 C CNN
	1    2600 900 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack_Switch J1
U 1 1 60963021
P 1050 1000
F 0 "J1" H 1107 1317 50  0000 C CNN
F 1 "Barrel_Jack_Switch" H 1107 1226 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 1100 960 50  0001 C CNN
F 3 "~" H 1100 960 50  0001 C CNN
	1    1050 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 609664F9
P 2150 1150
F 0 "C1" H 2242 1196 50  0000 L CNN
F 1 "10u" H 2242 1105 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 2150 1150 50  0001 C CNN
F 3 "~" H 2150 1150 50  0001 C CNN
	1    2150 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 60967944
P 3300 1350
F 0 "C2" H 3392 1396 50  0000 L CNN
F 1 "10u" H 3392 1305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 3300 1350 50  0001 C CNN
F 3 "~" H 3300 1350 50  0001 C CNN
	1    3300 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 6096885D
P 3700 1150
F 0 "C3" H 3792 1196 50  0000 L CNN
F 1 "150u" H 3792 1105 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 3700 1150 50  0001 C CNN
F 3 "~" H 3700 1150 50  0001 C CNN
	1    3700 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R3
U 1 1 6096C75E
P 2950 1050
F 0 "R3" H 3009 1096 50  0000 L CNN
F 1 "121" H 3009 1005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2950 1050 50  0001 C CNN
F 3 "~" H 2950 1050 50  0001 C CNN
	1    2950 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 6096D56D
P 2950 1350
F 0 "R4" H 3009 1396 50  0000 L CNN
F 1 "365" H 3009 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2950 1350 50  0001 C CNN
F 3 "~" H 2950 1350 50  0001 C CNN
	1    2950 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 1200 2950 1200
Wire Wire Line
	2950 1200 2950 1150
Wire Wire Line
	2950 1250 2950 1200
Connection ~ 2950 1200
Wire Wire Line
	2900 900  2950 900 
Wire Wire Line
	2950 900  2950 950 
Wire Wire Line
	2950 1200 3300 1200
Wire Wire Line
	3300 1200 3300 1250
Wire Wire Line
	2950 900  3700 900 
Wire Wire Line
	3700 900  3700 1050
Connection ~ 2950 900 
Wire Wire Line
	3700 1250 3700 1450
Wire Wire Line
	3700 1450 3300 1450
Connection ~ 3300 1450
Wire Wire Line
	3300 1450 2950 1450
Wire Wire Line
	2300 900  2150 900 
Wire Wire Line
	2150 900  2150 1050
Wire Wire Line
	2150 1250 2150 1450
Wire Wire Line
	2150 1450 2950 1450
Connection ~ 2950 1450
Connection ~ 2150 900 
Wire Wire Line
	1350 1000 1350 1100
Wire Wire Line
	1350 1100 1350 1450
Wire Wire Line
	1350 1450 2150 1450
Connection ~ 1350 1100
Connection ~ 2150 1450
$Comp
L power:+5V #PWR07
U 1 1 60977A05
P 3700 800
F 0 "#PWR07" H 3700 650 50  0001 C CNN
F 1 "+5V" H 3715 973 50  0000 C CNN
F 2 "" H 3700 800 50  0001 C CNN
F 3 "" H 3700 800 50  0001 C CNN
	1    3700 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 800  3700 900 
Connection ~ 3700 900 
Wire Wire Line
	1350 900  1650 900 
Wire Wire Line
	1650 800  1650 900 
Connection ~ 1650 900 
Wire Wire Line
	1650 900  1950 900 
Wire Wire Line
	2950 1500 2950 1450
$Comp
L power:PWR_FLAG #FLG01
U 1 1 60981CAA
P 1650 800
F 0 "#FLG01" H 1650 875 50  0001 C CNN
F 1 "PWR_FLAG" H 1650 973 50  0000 C CNN
F 2 "" H 1650 800 50  0001 C CNN
F 3 "~" H 1650 800 50  0001 C CNN
	1    1650 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 609833E0
P 2950 1500
F 0 "#PWR06" H 2950 1250 50  0001 C CNN
F 1 "GND" H 2955 1327 50  0000 C CNN
F 2 "" H 2950 1500 50  0001 C CNN
F 3 "" H 2950 1500 50  0001 C CNN
	1    2950 1500
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 60983639
P 2600 1500
F 0 "#FLG02" H 2600 1575 50  0001 C CNN
F 1 "PWR_FLAG" H 2600 1673 50  0000 C CNN
F 2 "" H 2600 1500 50  0001 C CNN
F 3 "~" H 2600 1500 50  0001 C CNN
	1    2600 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2600 1500 2950 1500
Connection ~ 2950 1500
$Comp
L power:+12V #PWR04
U 1 1 609853ED
P 1950 800
F 0 "#PWR04" H 1950 650 50  0001 C CNN
F 1 "+12V" H 1965 973 50  0000 C CNN
F 2 "" H 1950 800 50  0001 C CNN
F 3 "" H 1950 800 50  0001 C CNN
	1    1950 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 800  1950 900 
Connection ~ 1950 900 
Wire Wire Line
	1950 900  2150 900 
$Comp
L esp32-cam:esp32-cam U3
U 1 1 609B41F4
P 5350 1250
F 0 "U3" H 5350 1865 50  0000 C CNN
F 1 "esp32-cam" H 5350 1774 50  0000 C CNN
F 2 "esp32-cam:esp32-cam" H 5200 1400 50  0001 C CNN
F 3 "" H 5200 1400 50  0001 C CNN
	1    5350 1250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 609B6CA7
P 4800 750
F 0 "#PWR08" H 4800 600 50  0001 C CNN
F 1 "+5V" H 4815 923 50  0000 C CNN
F 2 "" H 4800 750 50  0001 C CNN
F 3 "" H 4800 750 50  0001 C CNN
	1    4800 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 750  4800 900 
Wire Wire Line
	4800 900  4950 900 
$Comp
L Sensor_Humidity:HDC1080 U1
U 1 1 6098B880
P 1300 2450
F 0 "U1" H 957 2496 50  0000 R CNN
F 1 "HDC1080" H 957 2405 50  0000 R CNN
F 2 "Package_SON:Texas_PWSON-N6" H 1250 2200 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/hdc1080.pdf" H 900 2700 50  0001 C CNN
	1    1300 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 6099285C
P 1650 2050
F 0 "#PWR03" H 1650 1900 50  0001 C CNN
F 1 "+5V" H 1665 2223 50  0000 C CNN
F 2 "" H 1650 2050 50  0001 C CNN
F 3 "" H 1650 2050 50  0001 C CNN
	1    1650 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2350 1650 2350
$Comp
L Device:R_Small R1
U 1 1 6099740E
P 1650 2150
F 0 "R1" H 1709 2196 50  0000 L CNN
F 1 "10k" H 1709 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 1650 2150 50  0001 C CNN
F 3 "~" H 1650 2150 50  0001 C CNN
	1    1650 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2250 1650 2350
Connection ~ 1650 2350
Wire Wire Line
	1650 2350 1750 2350
$Comp
L Device:R_Small R2
U 1 1 6099AE17
P 2000 2150
F 0 "R2" H 2059 2196 50  0000 L CNN
F 1 "10k" H 2059 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2000 2150 50  0001 C CNN
F 3 "~" H 2000 2150 50  0001 C CNN
	1    2000 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2450 2000 2250
Wire Wire Line
	1600 2450 2000 2450
Wire Wire Line
	2000 2450 2100 2450
Connection ~ 2000 2450
$Comp
L power:+5V #PWR05
U 1 1 6099CC57
P 2000 2050
F 0 "#PWR05" H 2000 1900 50  0001 C CNN
F 1 "+5V" H 2015 2223 50  0000 C CNN
F 2 "" H 2000 2050 50  0001 C CNN
F 3 "" H 2000 2050 50  0001 C CNN
	1    2000 2050
	1    0    0    -1  
$EndComp
Text GLabel 1750 2350 2    50   Input ~ 0
SCL
Text GLabel 4850 1100 0    50   Input ~ 0
SCL
Text GLabel 4850 1200 0    50   Input ~ 0
SDA
Text GLabel 2100 2450 2    50   Input ~ 0
SDA
Wire Wire Line
	4850 1100 4950 1100
Wire Wire Line
	4850 1200 4950 1200
Wire Wire Line
	1200 2050 1200 2150
$Comp
L power:+5V #PWR01
U 1 1 609A37DF
P 1200 2050
F 0 "#PWR01" H 1200 1900 50  0001 C CNN
F 1 "+5V" H 1215 2223 50  0000 C CNN
F 2 "" H 1200 2050 50  0001 C CNN
F 3 "" H 1200 2050 50  0001 C CNN
	1    1200 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 609A6F85
P 1200 2750
F 0 "#PWR02" H 1200 2500 50  0001 C CNN
F 1 "GND" H 1205 2577 50  0000 C CNN
F 2 "" H 1200 2750 50  0001 C CNN
F 3 "" H 1200 2750 50  0001 C CNN
	1    1200 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 609A7426
P 4950 1000
F 0 "#PWR09" H 4950 750 50  0001 C CNN
F 1 "GND" V 4955 872 50  0000 R CNN
F 2 "" H 4950 1000 50  0001 C CNN
F 3 "" H 4950 1000 50  0001 C CNN
	1    4950 1000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 609AA3D9
P 5850 1600
F 0 "#PWR010" H 5850 1350 50  0001 C CNN
F 1 "GND" H 5855 1427 50  0000 C CNN
F 2 "" H 5850 1600 50  0001 C CNN
F 3 "" H 5850 1600 50  0001 C CNN
	1    5850 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1600 5750 1600
$Comp
L Connector:Conn_01x03_Female J2
U 1 1 609BC5AB
P 6950 950
F 0 "J2" H 6978 976 50  0000 L CNN
F 1 "Conn_01x03_Female" H 6978 885 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Horizontal" H 6950 950 50  0001 C CNN
F 3 "~" H 6950 950 50  0001 C CNN
	1    6950 950 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 609BE00D
P 6700 850
F 0 "#PWR011" H 6700 700 50  0001 C CNN
F 1 "+5V" V 6715 978 50  0000 L CNN
F 2 "" H 6700 850 50  0001 C CNN
F 3 "" H 6700 850 50  0001 C CNN
	1    6700 850 
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 609BEC42
P 6750 950
F 0 "#PWR012" H 6750 700 50  0001 C CNN
F 1 "GND" V 6755 822 50  0000 R CNN
F 2 "" H 6750 950 50  0001 C CNN
F 3 "" H 6750 950 50  0001 C CNN
	1    6750 950 
	0    1    1    0   
$EndComp
Text GLabel 6750 1050 0    50   Input ~ 0
LED
Text GLabel 4850 1400 0    50   Input ~ 0
LED
Wire Wire Line
	4850 1300 4950 1300
$Comp
L LMP7721MA_NOPB:LMP7721MA_NOPB U6
U 1 1 60995BFA
P 8550 5250
F 0 "U6" H 8550 4583 50  0000 C CNN
F 1 "LMP7721MA_NOPB" H 8550 4674 50  0000 C CNN
F 2 "SOIC127P599X175-8N" H 8550 5250 50  0001 L BNN
F 3 "" H 8550 5250 50  0001 L BNN
F 4 "1.75mm" H 8550 5250 50  0001 L BNN "MAXIMUM_PACKAGE_HEIGHT"
F 5 "IPC-7351B" H 8550 5250 50  0001 L BNN "STANDARD"
F 6 "Texas Instruments" H 8550 5250 50  0001 L BNN "MANUFACTURER"
F 7 "E" H 8550 5250 50  0001 L BNN "PARTREV"
	1    8550 5250
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR021
U 1 1 6099C54A
P 9050 4000
F 0 "#PWR021" H 9050 3850 50  0001 C CNN
F 1 "+5V" V 9065 4128 50  0000 L CNN
F 2 "" H 9050 4000 50  0001 C CNN
F 3 "" H 9050 4000 50  0001 C CNN
	1    9050 4000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 6099D466
P 8050 3500
F 0 "#PWR016" H 8050 3250 50  0001 C CNN
F 1 "GND" H 8055 3327 50  0000 C CNN
F 2 "" H 8050 3500 50  0001 C CNN
F 3 "" H 8050 3500 50  0001 C CNN
	1    8050 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3900 8050 3900
Wire Wire Line
	7800 3700 7650 3700
Wire Wire Line
	7650 3700 7650 5450
Wire Wire Line
	7650 5450 8050 5450
Wire Wire Line
	7650 5450 7650 6050
Wire Wire Line
	7650 6050 9150 6050
Connection ~ 7650 5450
$Comp
L power:GND #PWR022
U 1 1 609A945E
P 9050 5750
F 0 "#PWR022" H 9050 5500 50  0001 C CNN
F 1 "GND" H 9055 5577 50  0000 C CNN
F 2 "" H 9050 5750 50  0001 C CNN
F 3 "" H 9050 5750 50  0001 C CNN
	1    9050 5750
	1    0    0    -1  
$EndComp
NoConn ~ 9050 4200
NoConn ~ 9050 4300
NoConn ~ 9050 4400
NoConn ~ 8050 4850
NoConn ~ 8050 4950
NoConn ~ 8050 5050
$Comp
L Device:R_Small R9
U 1 1 609AE882
P 9350 5200
F 0 "R9" H 9409 5246 50  0000 L CNN
F 1 "10k" H 9409 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9350 5200 50  0001 C CNN
F 3 "~" H 9350 5200 50  0001 C CNN
	1    9350 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 5350 9350 5350
$Comp
L Device:R_Small R10
U 1 1 609BA80B
P 9350 5500
F 0 "R10" H 9409 5546 50  0000 L CNN
F 1 "10k" H 9409 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9350 5500 50  0001 C CNN
F 3 "~" H 9350 5500 50  0001 C CNN
	1    9350 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 609BB087
P 9350 5600
F 0 "#PWR025" H 9350 5350 50  0001 C CNN
F 1 "GND" H 9355 5427 50  0000 C CNN
F 2 "" H 9350 5600 50  0001 C CNN
F 3 "" H 9350 5600 50  0001 C CNN
	1    9350 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 5000 9350 5100
$Comp
L power:GND #PWR024
U 1 1 609BF7CE
P 9350 4600
F 0 "#PWR024" H 9350 4350 50  0001 C CNN
F 1 "GND" H 9355 4427 50  0000 C CNN
F 2 "" H 9350 4600 50  0001 C CNN
F 3 "" H 9350 4600 50  0001 C CNN
	1    9350 4600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR026
U 1 1 609C0A65
P 10750 4900
F 0 "#PWR026" H 10750 4750 50  0001 C CNN
F 1 "+5V" H 10765 5073 50  0000 C CNN
F 2 "" H 10750 4900 50  0001 C CNN
F 3 "" H 10750 4900 50  0001 C CNN
	1    10750 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 5550 9150 5550
Wire Wire Line
	9150 5550 9150 6050
Wire Wire Line
	10750 5000 10750 4900
$Comp
L LM4140ACM-1.0:LM4140ACM-1.0 U7
U 1 1 609CDB7B
P 10050 4800
F 0 "U7" H 10050 4330 50  0000 C CNN
F 1 "LM4140ACM-1.0" H 10050 4421 50  0000 C CNN
F 2 "SOIC127P599X175-8N" H 10050 4800 50  0001 L BNN
F 3 "" H 10050 4800 50  0001 L BNN
	1    10050 4800
	-1   0    0    1   
$EndComp
Connection ~ 10750 4900
$Comp
L Device:C_Small C5
U 1 1 609CFF96
P 9100 5100
F 0 "C5" H 9192 5146 50  0000 L CNN
F 1 "1u" H 9192 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9100 5100 50  0001 C CNN
F 3 "~" H 9100 5100 50  0001 C CNN
	1    9100 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 5000 9350 5000
Connection ~ 9350 5000
$Comp
L power:GND #PWR023
U 1 1 609D1828
P 9100 5200
F 0 "#PWR023" H 9100 4950 50  0001 C CNN
F 1 "GND" H 9105 5027 50  0000 C CNN
F 2 "" H 9100 5200 50  0001 C CNN
F 3 "" H 9100 5200 50  0001 C CNN
	1    9100 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR017
U 1 1 609D2044
P 8050 5250
F 0 "#PWR017" H 8050 5100 50  0001 C CNN
F 1 "+5V" H 8065 5423 50  0000 C CNN
F 2 "" H 8050 5250 50  0001 C CNN
F 3 "" H 8050 5250 50  0001 C CNN
	1    8050 5250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial J3
U 1 1 6099EA21
P 7800 3900
F 0 "J3" H 7900 3782 50  0000 L CNN
F 1 "Conn_Coaxial" H 7900 3873 50  0000 L CNN
F 2 "digikey-footprints:RF_SMA_RightAngle_5-1814400-1" H 7800 3900 50  0001 C CNN
F 3 " ~" H 7800 3900 50  0001 C CNN
	1    7800 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	8050 3700 7950 3700
Wire Wire Line
	7950 3700 7950 3150
Wire Wire Line
	9000 3150 9000 3800
Wire Wire Line
	9000 3800 9050 3800
$Comp
L Device:R_Small R7
U 1 1 609D7CC8
P 8450 3150
F 0 "R7" V 8254 3150 50  0000 C CNN
F 1 "R_Small" V 8345 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8450 3150 50  0001 C CNN
F 3 "~" H 8450 3150 50  0001 C CNN
	1    8450 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 3150 8350 3150
Wire Wire Line
	8550 3150 9000 3150
$Comp
L Device:R_Small R5
U 1 1 609DB39C
P 7650 3300
F 0 "R5" H 7709 3346 50  0000 L CNN
F 1 "R_Small" H 7709 3255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7650 3300 50  0001 C CNN
F 3 "~" H 7650 3300 50  0001 C CNN
	1    7650 3300
	1    0    0    -1  
$EndComp
Connection ~ 7950 3150
$Comp
L power:GND #PWR013
U 1 1 609DD2AE
P 7650 3400
F 0 "#PWR013" H 7650 3150 50  0001 C CNN
F 1 "GND" H 7655 3227 50  0000 C CNN
F 2 "" H 7650 3400 50  0001 C CNN
F 3 "" H 7650 3400 50  0001 C CNN
	1    7650 3400
	1    0    0    -1  
$EndComp
$Comp
L LMP7721MA_NOPB:LMP7721MA_NOPB U5
U 1 1 6099209E
P 8550 4000
F 0 "U5" H 8550 4767 50  0000 C CNN
F 1 "LMP7721MA_NOPB" H 8550 4676 50  0000 C CNN
F 2 "SOIC127P599X175-8N" H 8550 4000 50  0001 L BNN
F 3 "" H 8550 4000 50  0001 L BNN
F 4 "1.75mm" H 8550 4000 50  0001 L BNN "MAXIMUM_PACKAGE_HEIGHT"
F 5 "IPC-7351B" H 8550 4000 50  0001 L BNN "STANDARD"
F 6 "Texas Instruments" H 8550 4000 50  0001 L BNN "MANUFACTURER"
F 7 "E" H 8550 4000 50  0001 L BNN "PARTREV"
	1    8550 4000
	1    0    0    -1  
$EndComp
Text GLabel 9050 3800 2    50   Input ~ 0
Vph
Wire Wire Line
	7650 3150 7650 3200
Wire Wire Line
	7650 3150 7950 3150
Wire Wire Line
	9350 5300 9350 5350
Wire Wire Line
	9350 5400 9350 5350
Connection ~ 9350 5350
Text GLabel 8950 2250 2    50   Input ~ 0
SDA
Text GLabel 8550 2150 2    50   Input ~ 0
SCL
NoConn ~ 8350 1950
$Comp
L power:GND #PWR019
U 1 1 60A211C9
P 8350 2350
F 0 "#PWR019" H 8350 2100 50  0001 C CNN
F 1 "GND" H 8355 2177 50  0000 C CNN
F 2 "" H 8350 2350 50  0001 C CNN
F 3 "" H 8350 2350 50  0001 C CNN
	1    8350 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R6
U 1 1 60A21F3D
P 8450 2000
F 0 "R6" H 8509 2046 50  0000 L CNN
F 1 "10k" H 8509 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8450 2000 50  0001 C CNN
F 3 "~" H 8450 2000 50  0001 C CNN
	1    8450 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 2250 8850 2250
$Comp
L Device:R_Small R8
U 1 1 60A2994C
P 8850 2000
F 0 "R8" H 8909 2046 50  0000 L CNN
F 1 "10k" H 8909 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8850 2000 50  0001 C CNN
F 3 "~" H 8850 2000 50  0001 C CNN
	1    8850 2000
	1    0    0    -1  
$EndComp
Connection ~ 8850 2250
Wire Wire Line
	8850 2250 8950 2250
Wire Wire Line
	8450 2150 8550 2150
Wire Wire Line
	8350 2150 8450 2150
Connection ~ 8450 2150
$Comp
L power:+5V #PWR020
U 1 1 60A2BCA6
P 8650 1850
F 0 "#PWR020" H 8650 1700 50  0001 C CNN
F 1 "+5V" H 8665 2023 50  0000 C CNN
F 2 "" H 8650 1850 50  0001 C CNN
F 3 "" H 8650 1850 50  0001 C CNN
	1    8650 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 1850 8850 1850
Wire Wire Line
	8450 2100 8450 2150
Wire Wire Line
	8450 1900 8450 1850
Wire Wire Line
	8450 1850 8650 1850
Connection ~ 8650 1850
Wire Wire Line
	8850 2100 8850 2250
Wire Wire Line
	8850 1900 8850 1850
$Comp
L Analog_ADC:ADS1115IDGS U4
U 1 1 60A1E2D4
P 7950 2150
F 0 "U4" H 7700 2600 50  0000 C CNN
F 1 "ADS1115IDGS" H 8250 2600 50  0000 C CNN
F 2 "Package_SO:TSSOP-10_3x3mm_P0.5mm" H 7950 1650 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ads1113.pdf" H 7900 1250 50  0001 C CNN
	1    7950 2150
	1    0    0    -1  
$EndComp
Text GLabel 7550 2050 0    50   Input ~ 0
Vph
$Comp
L power:+5V #PWR014
U 1 1 60A706C7
P 7950 1450
F 0 "#PWR014" H 7950 1300 50  0001 C CNN
F 1 "+5V" H 7965 1623 50  0000 C CNN
F 2 "" H 7950 1450 50  0001 C CNN
F 3 "" H 7950 1450 50  0001 C CNN
	1    7950 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 60A7112B
P 8150 1550
F 0 "C4" V 7921 1550 50  0000 C CNN
F 1 "0.1u" V 8012 1550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8150 1550 50  0001 C CNN
F 3 "~" H 8150 1550 50  0001 C CNN
	1    8150 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 1450 7950 1550
Wire Wire Line
	7950 1650 7950 1550
Connection ~ 7950 1550
Wire Wire Line
	7950 1550 8050 1550
$Comp
L power:GND #PWR018
U 1 1 60A79B05
P 8250 1550
F 0 "#PWR018" H 8250 1300 50  0001 C CNN
F 1 "GND" H 8400 1500 50  0000 C CNN
F 2 "" H 8250 1550 50  0001 C CNN
F 3 "" H 8250 1550 50  0001 C CNN
	1    8250 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 60A7B10E
P 7950 2550
F 0 "#PWR015" H 7950 2300 50  0001 C CNN
F 1 "GND" H 7955 2377 50  0000 C CNN
F 2 "" H 7950 2550 50  0001 C CNN
F 3 "" H 7950 2550 50  0001 C CNN
	1    7950 2550
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:DRV8871DDA U8
U 1 1 60AA9526
P 1350 3650
F 0 "U8" H 1100 3900 50  0000 C CNN
F 1 "DRV8871DDA" H 1650 3900 50  0000 C CNN
F 2 "Package_SO:Texas_HTSOP-8-1EP_3.9x4.9mm_P1.27mm_EP2.95x4.9mm_Mask2.4x3.1mm_ThermalVias" H 1600 3600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/drv8871.pdf" H 1600 3600 50  0001 C CNN
	1    1350 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 60AAD447
P 2000 3550
F 0 "J5" H 2080 3542 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 2080 3451 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 2000 3550 50  0001 C CNN
F 3 "~" H 2000 3550 50  0001 C CNN
	1    2000 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3550 1800 3550
Wire Wire Line
	1750 3650 1800 3650
$Comp
L power:GND #PWR028
U 1 1 60AB1AA7
P 950 3650
F 0 "#PWR028" H 950 3400 50  0001 C CNN
F 1 "GND" H 955 3477 50  0000 C CNN
F 2 "" H 950 3650 50  0001 C CNN
F 3 "" H 950 3650 50  0001 C CNN
	1    950  3650
	1    0    0    -1  
$EndComp
Text GLabel 950  3550 0    50   Input ~ 0
PUMP_IN
$Comp
L Connector:Screw_Terminal_01x02 J4
U 1 1 60AB78CB
P 1100 4200
F 0 "J4" H 1180 4192 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 1180 4101 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 1100 4200 50  0001 C CNN
F 3 "~" H 1100 4200 50  0001 C CNN
	1    1100 4200
	1    0    0    -1  
$EndComp
Text GLabel 1350 3350 1    50   Input ~ 0
VM+
Text GLabel 900  4200 0    50   Input ~ 0
VM+
$Comp
L Device:R_Small R_lim1
U 1 1 60ABAA23
P 1850 3950
F 0 "R_lim1" H 1909 3996 50  0000 L CNN
F 1 "15k" H 1909 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 1850 3950 50  0001 C CNN
F 3 "~" H 1850 3950 50  0001 C CNN
	1    1850 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3850 1850 3850
$Comp
L power:GND #PWR030
U 1 1 60ABF538
P 1850 4050
F 0 "#PWR030" H 1850 3800 50  0001 C CNN
F 1 "GND" H 1855 3877 50  0000 C CNN
F 2 "" H 1850 4050 50  0001 C CNN
F 3 "" H 1850 4050 50  0001 C CNN
	1    1850 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR029
U 1 1 60AC0710
P 1350 4050
F 0 "#PWR029" H 1350 3800 50  0001 C CNN
F 1 "GND" H 1355 3877 50  0000 C CNN
F 2 "" H 1350 4050 50  0001 C CNN
F 3 "" H 1350 4050 50  0001 C CNN
	1    1350 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 60AC245D
P 900 4300
F 0 "#PWR027" H 900 4050 50  0001 C CNN
F 1 "GND" H 905 4127 50  0000 C CNN
F 2 "" H 900 4300 50  0001 C CNN
F 3 "" H 900 4300 50  0001 C CNN
	1    900  4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 850  6750 850 
Text GLabel 4850 1300 0    50   Input ~ 0
PUMP_IN
Wire Wire Line
	4850 1400 4950 1400
$Comp
L Connector:Conn_01x04_Female J6
U 1 1 609FCDA8
P 3200 2300
F 0 "J6" H 3228 2276 50  0000 L CNN
F 1 "Conn_01x04_Female" H 3228 2185 50  0000 L CNN
F 2 "Connector_JST:JST_EH_S4B-EH_1x04_P2.50mm_Horizontal" H 3200 2300 50  0001 C CNN
F 3 "~" H 3200 2300 50  0001 C CNN
	1    3200 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR031
U 1 1 609FF7DE
P 3000 2200
F 0 "#PWR031" H 3000 2050 50  0001 C CNN
F 1 "+5V" H 3015 2373 50  0000 C CNN
F 2 "" H 3000 2200 50  0001 C CNN
F 3 "" H 3000 2200 50  0001 C CNN
	1    3000 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 60A00194
P 3000 2400
F 0 "#PWR032" H 3000 2150 50  0001 C CNN
F 1 "GND" V 3005 2272 50  0000 R CNN
F 2 "" H 3000 2400 50  0001 C CNN
F 3 "" H 3000 2400 50  0001 C CNN
	1    3000 2400
	0    1    1    0   
$EndComp
Text GLabel 3000 2500 0    50   Input ~ 0
SCL
Text GLabel 3000 2300 0    50   Input ~ 0
SDA
$EndSCHEMATC
