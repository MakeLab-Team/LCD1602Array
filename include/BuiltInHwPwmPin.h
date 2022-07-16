#ifndef __BuiltInHwPwmPin_h
#define __BuiltInHwPwmPin_h

#include <Arduino.h>
#include "PwmOutput.h"

class BuiltInHwPwmPin : public PwmOutput {
private:
  uint8_t _pin;
  int floatToInt(float f) {return f*256.99;}

public:
  BuiltInHwPwmPin(uint8_t pin) {
    _pin=pin;
    pinMode(pin, OUTPUT);
  }

  void setValue(float val) {
    int v = floatToInt(val);
    if (v==256) {
      digitalWrite(_pin, HIGH);
    } else
    analogWrite(_pin,v);
  }
};

#endif // __BuiltInHwPwmPin_h
