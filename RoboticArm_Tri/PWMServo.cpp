#include "PWMServo.h"

//#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)  // minimum value in uS for this servo
//#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)  // maximum value in uS for this servo
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
bool pwm_initialized= false;

pwmServo::pwmServo() {

}

uint8_t pwmServo::attach(int pin) {
    this->servoIndex = pin;    
    if (!pwm_initialized) {
        pwm.begin();
        pwm.setOscillatorFrequency(27000000);
        pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
        pwm_initialized = true;
        Serial.println("PWM initialized");
    }
    Serial.print("PWM attached ");
    Serial.println(pin);
}

void pwmServo::write(double value) {
    if(value < 0) value = 0;
    if(value > 180) value = 180;
    ang = value;
    value = map(value, 0, 180, SERVOMIN,  SERVOMAX);
    pwm.setPWM(this->servoIndex,0,value);
}

double pwmServo::map_double(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double pwmServo::read() {
    //return  map( pwm.getPWM(this->servoIndex), SERVOMIN, SERVOMAX, 0, 180);
    return ang;
}
