#include "Trigonometric.h"
#include "math.h"
#define DEBUG1

// Default ARM length
double L1=7.9;
double L2=7.9;
double L1_s = L1*L1;
double L2_s = L2*L2;
double left_adjust;
double right_adjust;

void setArmLength(double upper, double lower) {
  L1 = upper;
  L2 = lower;
  L1_s = upper*upper;
  L2_s = lower*lower;
}

// from x, y get angle alpha & beta
bool solve(double x, double y, double &alpha, double &beta) {
  double L3_s = (x*x+y*y);
  double L3   = sqrt(L3_s);

  double cosa = (L3_s + L2_s - L1_s)/(2*L3*L2);
  if (cosa > 1) return false;
  double a = acos(cosa);
  double theta = asin(y/L3);
  alpha = PI - a - theta;
  
  double b = acos((L1_s + L2_s - L3_s)/(2*L1*L2));
  beta = alpha-b;
  
#ifdef DEBUG
  Serial.print("\nsolve: ");
  Serial.print("x=");
  Serial.print(x);
  Serial.print("\ty=");
  Serial.println(y);
  Serial.print("\tL3^2=");
  Serial.print(L3_s);
  Serial.print("\tL3=");
  Serial.print(L3);
  Serial.println("\talpha=");
  Serial.print(r2d(alpha));
  Serial.print("\tbeta=");
  Serial.print(r2d(beta));
  Serial.println();
#endif
  return true;
}

bool unsolve(double alpha, double beta, double &x, double &y){ 
   double a3 = alpha - beta;
   double L3_s = (L1_s+L2_s)-((2*L1*L2)*cos(a3));
   double L3 = sqrt(L3_s);

   double a2 = acos((L3_s + L1_s - L2_s)/(2*L3*L1));
   double theta = PI - a2 - alpha;

   y = L3*sin(theta);
   x = L3*cos(theta);

#ifdef DEBUG
  Serial.print("\nunsolve: ");
  Serial.print("x=");
  Serial.print(x);
  Serial.print("\ty=");
  Serial.print(y);
  Serial.print("\tL3^2=");
  Serial.print(L3_s);
  Serial.print("\tL3=");
  Serial.print(L3);
  Serial.println("\talpha=");
  Serial.print(r2d(alpha));
  Serial.print("\tbeta=");
  Serial.print(r2d(beta));
  Serial.println();
#endif
   return 1;
}

double r2d(double r) {
  return (r*180)/PI;
}

double d2r(double d) {
  return (d*PI)/180;
}
