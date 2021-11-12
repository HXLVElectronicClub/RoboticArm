#include <Servo.h>
#define SERVOPIN_CLAW 9
#define SERVOPIN_LEFT 11
#define SERVOPIN_RIGHT 10
#define SERVOPIN_BOTTOM 6
#define AX A0
#define AY A1

#define SW 8
#define BTN 7

Servo claw, left, right, bottom;
int claw_close=20,claw_open=0;
int max_left=175, min_left=80;
int max_right=180, min_right = 53;
int max_bottom=180, min_bottom=0;
int btn_counter=0;

void setup() {
  Serial.begin(9600);
  pinMode(BTN,INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  left.attach(SERVOPIN_LEFT);
  right.attach(SERVOPIN_RIGHT);
  claw.attach(SERVOPIN_CLAW);
  bottom.attach(SERVOPIN_BOTTOM);
  //left.write(max_left);
  //right.write(min_right);
  //claw.write(claw_close);
  //bottom.write(90);
}

void loop() {
  int ax = analogRead(AX);
  int ay = analogRead(AY);
  int btn = digitalRead(BTN);
  int sw = digitalRead(SW);

  if (ax < 500) {
      left.write(left.read() -1);
    //bottom.write(bottom.read()-1);
  } else if (ax > 600) {
    left.write(left.read() +1);
    //bottom.write(bottom.read()+1);
  } 
  if (ay < 500) {
    right.write(right.read() -1);
  } else if (ay > 600 ) {
    right.write(right.read() +1);
  }
//  
//  if (ax < 500 && left.read() > min_left) {
//      left.write(left.read() -1);
//    //bottom.write(bottom.read()-1);
//  } else if (ax > 600) {left.read() < max_left) {
//    left.write(left.read() +1);
//    //bottom.write(bottom.read()+1);
//  } 
//  if (ay < 500 && right.read() > min_right) {
//    right.write(right.read() -1);
//  } else if (ay > 600 && right.read() < max_right) {
//    right.write(right.read() +1);
//  }

  if (sw == 0) {
    claw.write(claw.read()-1);
  } else if (btn == 0) {
    claw.write(claw.read()+1);
  }

//
//  if (btn==0) {
//    if (btn_counter < 5) {
//      btn_counter ++;
//    } else {
//      if (claw.read() == claw_open) {
//        claw.write(claw_close);
//      } else {
//        claw.write(claw_open);
//      }
//      btn_counter = 0;
//    }
//  } else {
//    btn_counter = 0;
//  }
  
  Serial.print("X=");
  Serial.print(ax);
  Serial.print("\tY=");
  Serial.print(ay);
  Serial.print("\t SW=");
  Serial.print(sw);
  Serial.print("\t BTN=");
  Serial.print(btn);
  Serial.print("\t left=");
  Serial.print(left.read());
  Serial.print("\t rigt=");
  Serial.print(right.read());
  Serial.print("\t claw=");
  Serial.print(claw.read());
  Serial.print("\t bot=");
  Serial.print(bottom.read());
  Serial.println("");
  
}
