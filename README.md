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
The LCD displayed are arranged an designated with two codes, one for the backlight (prefix W/X/Y/Z,)and the other for the content (prefix J/K.) The arrangement is as follows:

| Row0  | Row1  | Row2  | Row3  |
|-------|-------|-------|-------|
| J0/W0 | K0/X0 | J0/Y0 | K0/Z0 |
| J1/W1 | K1/X1 | J1/Y1 | K1/Z1 |
| J2/W2 | K2/X2 | J2/Y2 | K2/Z2 |
| J0/W3 | K0/X3 | J0/Y3 | K0/Z3 |
| J1/W4 | K1/X4 | J1/Y4 | K1/Z4 |
| J2/W5 | K2/X5 | J2/Y5 | K2/Z5 |
| J0/W6 | K0/X6 | J0/Y6 | K0/Z6 |
| J1/W7 | K1/X7 | J1/Y7 | K1/Z7 |
| J2/W8 | K2/X8 | J2/Y8 | K2/Z8 |

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
|   6 | only W8: LED+ (A)|
|   7 | only J0: EN |
|   8 | only J1: EN |
|   9 | only X8: LED+ (A)|
|  10 | only Y8: LED+ (A)|
|  11 | only Z8: LED+ (A)|
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
| PWMDRV0 PWM pin 0-7  | W0-7: LED+ (A) |
| PWMDRV0 PWM pin 8-15 | X0-7: LED+ (A) |
| PWMDRV1 PWM pin 0-7  | Y0-7: LED+ (A) |
| PWMDRV1 PWM pin 8-15 | Z0-7: LED+ (A) |

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
