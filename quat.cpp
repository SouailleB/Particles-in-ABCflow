#include"point.h"
#include"matrix.h"
#include"quat.h"
#include<iostream>
#include<cmath>
#include<vector>

//Constructors------------------------------------------------------
quaternion::quaternion():scalar(0){}

quaternion::quaternion(double angle, double n1, double n2, double n3): scalar(cos(angle/2)){
  vector.set(0,n1);
  vector.set(1,n2);
  vector.set(2,n3);
  vector/=vector.norm();
  vector*=sin(angle/2);
}
quaternion::quaternion(double angle, point v): scalar(cos(angle/2)), vector(sin(angle/2)*(v/v.norm())){}
quaternion::quaternion(const quaternion& q): scalar(q.scalar), vector(q.vector){}

//Methods-----------------------------------------------------------
void quaternion::set(int n, double x){
  if(n==0) scalar = x;
  else vector.set(n-1,x);
}
double quaternion::get(int n){
  double x;
  x = (n==0) ? scalar : vector.get(n-1);
  return x;
}

void quaternion::set_scalar(double s){scalar = s;}
void quaternion::set_vector(point  v){vector = v;}

void quaternion::set_aa(double angle, point axis){
  scalar = cos(angle/2);
  vector = sin(angle/2)*(axis/axis.norm());
}

double quaternion::get_scalar(){return scalar;}
point  quaternion::get_vector(){return vector;}

double quaternion::get_angle(){return 2*acos(scalar);}
point  quaternion::get_axis(){return vector/vector.norm();}
quaternion quaternion::conjugate(){
  quaternion q;
  q.scalar =    scalar;
  q.vector = -1*vector;
  return q;
}

double quaternion::norm(){return sqrt(scalar*scalar+(vector|vector));}

void quaternion::normalize(){
  double n = sqrt(scalar*scalar+(vector|vector));
  scalar/=n;
  vector/=n;
}

point quaternion::lab2bff(point r){
  point w(2*(vector|r)*vector+scalar*scalar*r+2*scalar*(r*vector)-(vector|vector)*r);
  return w;
}

point quaternion::bff2lab(point r){
  point w(2*(vector|r)*vector+scalar*scalar*r+2*scalar*(vector*r)-(vector|vector)*r);
  return w;
}

matrix quaternion::rot_mat(){
  matrix R(3);
  double a = scalar;
  double b = vector.get(0);
  double c = vector.get(1);
  double d = vector.get(2);
  
  R.set(0,0,a*a+b*b-c*c-d*d); R.set(0,1,    2*(b*c+a*d)); R.set(0,2,    2*(b*d-a*c));

  R.set(1,0,    2*(b*c-a*d)); R.set(1,1,a*a-b*b+c*c-d*d); R.set(1,2,    2*(c*d+a*b));

  R.set(2,0,    2*(b*d+a*c)); R.set(2,1,    2*(c*d-a*b)); R.set(2,2,a*a-b*b-c*c+d*d);

  return R;
}

point quaternion::lab2bff_2(point r){
  matrix R(3);
  double a = scalar;
  double b = vector.get(0);
  double c = vector.get(1);
  double d = vector.get(2);
  
  R.set(0,0,a*a+b*b-c*c-d*d); R.set(0,1,    2*(b*c+a*d)); R.set(0,2,    2*(b*d-a*c));

  R.set(1,0,    2*(b*c-a*d)); R.set(1,1,a*a-b*b+c*c-d*d); R.set(1,2,    2*(c*d+a*b));

  R.set(2,0,    2*(b*d+a*c)); R.set(2,1,    2*(c*d-a*b)); R.set(2,2,a*a-b*b-c*c+d*d);

  return R.act(r);
}
point quaternion::bff2lab_2(point r){
  matrix R(3);
  double a = scalar;
  double b = -vector.get(0);
  double c = -vector.get(1);
  double d = -vector.get(2);
  
  R.set(0,0,a*a+b*b-c*c-d*d); R.set(0,1,    2*(b*c+a*d)); R.set(0,2,    2*(b*d-a*c));
  
  R.set(1,0,    2*(b*c-a*d)); R.set(1,1,a*a-b*b+c*c-d*d); R.set(1,2,    2*(c*d+a*b));
  
  R.set(2,0,    2*(b*d+a*c)); R.set(2,1,    2*(c*d-a*b)); R.set(2,2,a*a-b*b-c*c+d*d);

  return R.act(r);
}
  

void quaternion::display_sv(){
  std::cout << scalar << '\t' << vector.get(0) << '\t' << vector.get(1) << '\t' << vector.get(2) << std::endl;
}

void quaternion::display_aa(){
  point n(vector/vector.norm());
  std::cout << 2*acos(scalar) << '\t' << n.get(0) << '\t' << n.get(1) << '\t' << n.get(2) << std::endl;
}

//Binary Operators------------------------------------------------

quaternion operator+(const quaternion & q1,const quaternion & q2){
  quaternion q(q1.scalar + q2.scalar, q1.vector + q2.vector);
  return q;
}
quaternion operator-(const quaternion & q1,const quaternion & q2){
  quaternion q(q1.scalar - q2.scalar, q1.vector - q2.vector);
  return q;
}
quaternion operator*(const double & a, const quaternion & q){
  quaternion p;
  p.scalar = a*q.scalar;
  p.vector = a*q.vector;
  return p;
}

quaternion operator*(const quaternion & q1,const quaternion & q2){

  double w1 = q1.scalar;
  double w2 = q2.scalar;
  point v1(q1.vector);
  point v2(q2.vector);
  double w = (w1*w2)-(v1|v2);
  point  v((w1*v2)+(w2*v1)+(v1*v2));

  quaternion q;
  q.scalar = w;
  q.vector = v;
  return q;
}

quaternion operator*(const quaternion & q,const point & u){
  double s = q.scalar;
  point  v = q.vector;

  double s_res = -(v|u);
  point  v_res(s*u+v*u);

  quaternion res;
  res.scalar = s_res;
  res.vector = v_res;  
  return res;
}

quaternion operator*(const point & u,const quaternion & q){
  double s = q.scalar;
  point  v = q.vector;

  double s_res = -(v|u);
  point  v_res(s*u+u*v);

  quaternion res;
  res.scalar = s_res;
  res.vector = v_res;
  return res;
}

std::ostream& operator<<(std::ostream& os, const quaternion& q){
  os << q.scalar << '\t' << q.vector;
  return os;
}

//Unitary Operators----------------------------------------
quaternion & quaternion::operator=(const quaternion & q){
  if(&q!=this){
    scalar = q.scalar;
    vector = q.vector;
  }
  return *this;
}

quaternion & quaternion::operator+=(const quaternion & q){
  scalar += q.scalar;
  vector += q.vector;
  return *this;
}

quaternion & quaternion::operator*=(const double & a){
  scalar*=a;
  vector*=a;
  return *this;
}
