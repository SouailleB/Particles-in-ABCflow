#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include"point.h"
#include"matrix.h"
#include"quat.h"


struct rigid_body{
  //rigid_body(const rigid_body& rb);
  void display();
  
  double mass;
  matrix ang_inertia;
  matrix inv_ang_in;
  point position;
  quaternion orientation;
  point lin_momentum;
  point ang_momentum;
};

void rb2array(rigid_body rb, double y[]);
void array2rb(rigid_body &rb, double y[]);

#endif
