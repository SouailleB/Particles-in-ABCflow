#ifndef POINT_H
#define POINT_H

#include<vector>
#include<iostream>
#include<ostream>

class point{

 public:
  //Constructors-----------------------------------
  point();
  point(double x, double y, double z); //By default, 3D vector
  point(const point& v);
  point(int n);
  point(int n, double x);


  //Setters and Getters-------------------------------
  int size();
  double get(int i);
  void set(int i, double x); //Set the x value at the i-th place

  //Methods------------------------------------------
  double norm();
  double max();
  void display();
  void print(std::string namef);

  //Binary operators----------------------------------------
  friend point  operator+(const point  & v, const point  & w);
  friend point  operator-(const point  & v, const point  & w);
  friend point  operator*(const point  & v, const point  & w); //cross product
  friend point  operator*(const double & a, const point  & v); //product by a real number
  friend point  operator/(const point  & v, const double & a); //division by a real number
  friend double operator|(const point  & v, const point  & w); //dot product

  friend std::ostream& operator<<(std::ostream& os, const point& v);

  //Unitary operators----------------------------------------
  point &  operator=(const point  & v);
  point & operator+=(const point  & v);
  point & operator-=(const point  & v);
  point & operator*=(const double & a);
  point & operator/=(const double & a);
  
  
 private:
  std::vector<double> values;
  int dimension;
};

#endif
