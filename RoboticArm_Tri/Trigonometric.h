// Solve servo angles according to claw position
// or reverse wise
//            B
//          //|
//       L1//||
//        // ||L2
//     >>||  ||  
//       C  |-o-|    
//          |_A_|
//                                ^ Y              B
//     (x,y)C _____L1____ B       |                /\
//            \c       b/         |               /  \
//             \       /          |           L1 /    \  L2
//           L3 \     / L2        |             /      \ 
//               \   /            |          C /_beta_  \
//   X            \a/           -X|    X /_ _ _ _ _ _ _ _\_alpha_ -X
// /_ _ _ _ _theta_V_alpha_ _ _ _ |                      A
// \               A(0,0)                     
//                                           
// right servo angle alpha = /_ BA(-X)
// left servo angle  beta  = /_ BC(-X)
// upper arm L1 = CB
// vertical arm L2 = AB
// Distance between claw and A L3 = AC

// L3^2 = x^2 + y^2
// cos(/_CBA) = (L1^2 + L2^2 - L3^2)/(2*L1*L2)
// cos(/_BAC) = (L3^2 + L2^2 - L1^2)/(2*L2*L3)
// cos(theta) = y/L3
// alpha = PI - theta - /_BAC
// beta = alpha - /_CBA

#include<Arduino.h>

#ifndef TRIGONOMETRIC_H
#define TRIGONOMETRIC_H

#ifndef PI
  #define PI 3.14159265
#endif

void setArmLength(double upper, double lower);
// from coordinate to angles
bool solve(double x, double y, double &a, double &b);
// from angles get cordinate
bool unsolve(double a, double b, double &x, double &y);
double r2d(double r);
double d2r(double d);
#endif
