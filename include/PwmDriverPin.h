#ifndef __PwmDriverPin_h
#define __PwmDriverPin_h

#include "PwmOutput.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class PwmDriverPin : public PwmOutput
{
private:
  Adafruit_PWMServoDriver &_driver;
  uint8_t _pin;
  int floatToInt(float f) {return f*4096.99;}

public:
  PwmDriverPin(Adafruit_PWMServoDriver &driver, uint8_t pin) :
    _driver(driver) {
      _pin = pin;
  }

  void setValue(float value) {
    int v = floatToInt(value);
    if (v == 0) {
      _driver.setPWM(_pin, 0, 4096);  // strange, but this is how adafruit doc says to turn fully off
    } else if (v == 4096) {
      _driver.setPWM(_pin, 4096, 0); // strange, but this is how adafruit doc says to turn fully on
    } else {
      _driver.setPWM(_pin, 0, v);
    }
  }

};

#endif //__PwmDriverPin_h
