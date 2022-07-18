# LCD1602Array

Control 4x9 matrix of 16x2 LCD displays.
The backlight of each display is controlled individually.
The only 6 display content is controlled, but each is duplicated 6 times

## Hardware

### The components:
36 LCD1602 displays.<br/>
Strip boards, since all but 2 LCD pins are connected the same way.<br/>
1 Arduino Nano compatible board.<br/>
2 *Modified* Adafruit PCA9685 16-Channel Servo Driver, modification described below.<br/>
2 Push Bottons.<br/>
1 trimmer potentiometer (10K or higher.)<br/>

*Servo Driver Modifications:* In the Servo drivers all 16 channel resistors are replace with jumper / 0 Ohm resistors.<br/>
The servo drivers are denoted PWMDRV0 and PWMDRV1, PWMDRV1 has A0 pad soldered together so that it's I2C address is 0x41.<br/>

### LCD display arrangment and designation
The LCD displayed are arranged an designated with two codes, one for the backlight (prefix E/F/G/H,)and the other for the content (prefix J/K.) The arrangement is as follows:

| Row0  | Row1  | Row2  | Row3  |
|-------|-------|-------|-------|
| J0/E0 | K0/H0 | J0/G0 | K0/H0 |
| J1/E1 | K1/H1 | J1/G1 | K1/H1 |
| J2/E2 | K2/H2 | J2/G2 | K2/H2 |
| J0/E3 | K0/H3 | J0/G3 | K0/H3 |
| J1/E4 | K1/H4 | J1/G4 | K1/H4 |
| J2/E5 | K2/H5 | J2/G5 | K2/H5 |
| J0/E6 | K0/H6 | J0/G6 | K0/H6 |
| J1/E7 | K1/H7 | J1/G7 | K1/H7 |
| J2/E8 | K2/H8 | J2/G8 | K2/H8 |

### Connections between the Nano and PWMDRVx:

| Nano | PWMDRVx |
|------|-----|
| GND  | GND |
| 5V   | VCC |
| A4   | SDA |
| A5   | SDL |

### LCD1602 pin Designations:
The pin designation, left to right when the front side is up, and oriented so the pins are at the top:<br/>
VSS, VDD, V0, RS, RW, W, D0, D1, D2, D3, D4, D5, D6, D7, LCD+ (A), LCD- (K).

### Connections between the Nano and the LCD displays:

| Nano | LCD |
|------|-----|
|   2 | D7 |
|   3 | D6 |
|   4 | D5 |
|   5 | D4 |
|   6 | only F8: LED+ (A)|
|   7 | only J0: EN |
|   8 | only J1: EN |
|   9 | only E8: LED+ (A)|
|  10 | only H8: LED+ (A)|
|  11 | only G8: LED+ (A)|
|  12 | RS |
|  A0 | only J2: EN |
|  A1 | only K0: EN |
|  A2 | only K1: EN |
|  A3 | only K2: EN |
|  5V | VDD |
| GND | VSS, V0, RW, LED- (K)

### Connections between PWMDRVs and LCDs:
| PWMDRVx pin | LCD |
|-------------|-----|
| PWMDRV0 PWM pin 0-7  | F0-7: LED+ (A) |
| PWMDRV0 PWM pin 8-15 | E0-7: LED+ (A) |
| PWMDRV1 PWM pin 0-7  | G0-7: LED+ (A) |
| PWMDRV1 PWM pin 8-15 | H0-7: LED+ (A) |

### Important note about the LCD backlight
The LCD displays we're using accepts 5V for the backlight, and consumes a very small current. <br/>
In the unlikely case that you want to build this project too, and use a LCD from a different manufacturer, the backlight specs may differ.<br/>
You may need to put resistors before each LCD+ (A) (each one is connected seperatly.) <br/>
If you have a backlight that consumes more current that the arduino or servo driver can handle you need to do the followings:<br/>
* Use 5 darlington array ULN2803, and use connect what is connected in the description above to an in pin, and the out pin to the original LED+ (A) it was supposed to be connected.  
* The COM in the ULN2803 should be connected to the proper voltage the backlight works properly with. (you don't need the resistors if you set the voltage properly.)
* The GND of the ULN2803 are naturally connected to GND.
* You don't need to bypass the resisors in the Servo Driver in this case.

### Additional connections:
One push button doubles as a reset connecting when pushed the NANO RST pin to GND.<br/>
The other push button used as a test button, to be used in conjuction to the reset button to enter test mode. The test button connects when pushed between the NANO 13 pin and GND.<br/>
The trimmer pottentiometer used as a voltage divider connenting to the NANO A6 pin (and 5V and GND.) it is used as a test selection in test mode.<br/>
