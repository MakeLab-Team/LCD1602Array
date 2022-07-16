#ifndef __PwmOutput_h
#define __PwmOutput_h


#include <Arduino.h>

class PwmOutput {
public:
  virtual void setValue(float val) = 0; // value between 0 and 1
  virtual ~PwmOutput() {}
};

#endif // __PwmOutput_h
