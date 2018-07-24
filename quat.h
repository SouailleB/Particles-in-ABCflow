#ifndef QUAT_H
#define QUAT_H

class matrix;

#include"matrix.h"

class quaternion{
 public:
  //Constructors---------------------------------------------------
  quaternion();
  quaternion(double p, double nx, double ny, double nz);
  quaternion(double p, point n);
  quaternion(const quaternion& q);

  //Methods-------------------------------------------------------
  void   set(int n, double x);
  double get(int n);
  
  void set_scalar(double s);
  void set_vector(point  v);
  void set_aa(double angle, point axis);

  double get_scalar();
  point  get_vector();
  
  double get_angle();
  point get_axis();
  quaternion conjugate();
  double norm();
  void normalize();
  point lab2bff(point r);
  point bff2lab(point r);

  point lab2bff_2(point r);
  point bff2lab_2(point r);
  
  void display_sv();
  void display_aa();
  matrix rot_mat();

  
  //Binary Operators---------------------------------------------------
  friend quaternion operator+(const quaternion & q1,const quaternion & q2);
  friend quaternion operator-(const quaternion & q1,const quaternion & q2);
  friend quaternion operator*(const double     & a, const quaternion &  q);
  friend quaternion operator*(const quaternion & q1,const quaternion & q2);
  friend quaternion operator*(const quaternion & q,const point & v);
  friend quaternion operator*(const point & v,const quaternion & q);

  friend std::ostream& operator<<(std::ostream& os,const quaternion& q);
  //Unitary Operators-------------------------------------------------
  quaternion &  operator=(const quaternion & q);
  quaternion & operator+=(const quaternion & q);
  quaternion & operator*=(const double & a);
  
 private:
  double scalar;
  point vector;
};

#endif
