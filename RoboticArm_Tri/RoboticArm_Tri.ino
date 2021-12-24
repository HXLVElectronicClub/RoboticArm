#define DEBUG

#include "PWMServo.h"
#include "Trigonometric.h"

#define SERVOPIN_CLAW 0
#define SERVOPIN_LEFT 1
#define SERVOPIN_RIGHT 2
#define SERVOPIN_BOTTOM 3
#define AX A0
#define AY A1

#define SW   7
#define BTN  8
#define BTN2 9
#define BTN3 10
#define BTN4 11

#define UPPER_ARM_LEN 7.9
#define LOWER_ARM_LEN 7.9

pwmServo claw, left, right, bottom;

// Servo angle limitations
int claw_close=29,claw_open=45;
int max_left=120, min_left=15;
int max_right=89, min_right = 15;
int mid_bottom=16;
int left_horizontal=107;
int right_vertical=45;

int sw_counter=0;

void toggle_claw(int open=-1) {
   int claw_angle;
   if (open == -1) {
      claw_angle = claw.read();
      if (claw_angle == claw_open) {
        claw_angle = claw_close;
      } else {
        claw_angle = claw_open;   
      }
   } else if (open == 1) {
      claw_angle = claw_open;
   } else {
      claw_angle = claw_close;
   }
   claw.write(claw_angle);
}

void setup() {
  Serial.begin(9600);
  pinMode(BTN,INPUT_PULLUP);
  pinMode(BTN2,INPUT_PULLUP);
  pinMode(BTN3,INPUT_PULLUP);
  pinMode(BTN4,INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  left.attach(SERVOPIN_LEFT);
  right.attach(SERVOPIN_RIGHT);
  claw.attach(SERVOPIN_CLAW);
  bottom.attach(SERVOPIN_BOTTOM);
  setArmLength(UPPER_ARM_LEN,LOWER_ARM_LEN);
  move_servo(left_horizontal, right_vertical);
  toggle_claw(0);
  bottom.write(mid_bottom);
}

void loop() {
  int ax   = analogRead(AX);
  int ay   = analogRead(AY);
  int btn  = digitalRead(BTN);
  int btn2 = digitalRead(BTN2);
  int btn3 = digitalRead(BTN3);
  int btn4 = digitalRead(BTN4);
  int sw   = digitalRead(SW);

  double deltax=0, deltay=0;
  if (ax < 350) {
    deltay = 0.3;
  } if (ax > 700) {
    deltay = -0.3;
  } 
  if (ay < 350) {
    deltax = -0.3;
  } else if (ay > 700 ) {
    deltax = 0.3;
  }
  if (deltax !=0 || deltay !=0) {
    double x, y;
    get_claw_pos(x,y);
    move_to(x+deltax,y+deltay);
  }
  
  if (sw==0) { // SW pressed, count for 5 times in order to avoid glitch
    if (sw_counter < 4) {
      sw_counter ++;
    } else {
      toggle_claw();
      sw_counter = 0;
    }
  } else {
    sw_counter = 0;
  }

  if (btn==0) {
    move_to(12, 7);
    toggle_claw();
  }

#ifdef DEBUG
//  Serial.print("X=");
//  Serial.print(ax);
//  Serial.print("\tY=");
//  Serial.print(ay);
//  Serial.print("\t SW=");
//  Serial.print(sw);
//  Serial.print("\t BTN=");
//  Serial.print(btn);
  Serial.print("left=");
  Serial.print(left.read());
  Serial.print("\t right=");
  Serial.print(right.read());
  Serial.print("\t claw=");
  Serial.print(claw.read());
  Serial.print("\t bot=");
  Serial.print(bottom.read());
  double x, y;
  get_claw_pos(x,y);
  Serial.println("");
#endif
}

// get servo angles for a coordinate
void get_angles_by_claw_pos(double &left_angle, double &right_angle, double x, double y) {
  double alpha, beta;
  if (solve(x, y, alpha, beta)) {
    right_angle = r2d(alpha) - right_vertical;
    left_angle = left_horizontal - r2d(beta);
  }
}

// get current claw position according to servo angles
void get_claw_pos(double &x, double &y) {
  double alpha, beta;
  alpha = d2r(right.read() + right_vertical);
  beta  = d2r(left_horizontal - left.read());
  unsolve(alpha, beta, x, y);
  #ifdef DEBUG
    Serial.print(" x=");
    Serial.print(x);
    Serial.print("\ty=");
    Serial.print(y);
    Serial.print("\talpha=");
    Serial.print(r2d(alpha));
    Serial.print("\tbeta =");
    Serial.print(r2d(beta));
  #endif
}

void move_to(double x, double y) {
  double left_angle = left.read(), right_angle = right.read();
  get_angles_by_claw_pos(left_angle,right_angle,x, y);
  if (right_angle > max_right) right_angle = max_right;
  if (right_angle < min_right) right_angle = min_right;  
  if (left_angle > max_left) left_angle = max_left;
  if (left_angle < min_left) left_angle = min_left;
  move_servo(left_angle, right_angle);
}

void move_servo(double left_angle, double right_angle) {
  left.write(left_angle);
  right.write(right_angle);
}
