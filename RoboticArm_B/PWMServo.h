#ifndef PWMSERVO_H
#define PWMSERVO_H

#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached

class pwmServo {
  public:
    pwmServo();
    uint8_t attach(int pin);
    void write(int value);
    int read();
  private:
    uint8_t servoIndex;
    uint8_t ang;
    int8_t min;
    int8_t max;
};

#endif
