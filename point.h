#ifndef POINT_H
#define POINT_H

#include<vector>
#include<iostream>
#include<ostream>

class point{

 public:
  //Constructors-----------------------------------
  point();
  point(double x, double y, double z);
  point(const point& v);
  point(int n);
  point(int n, double x);


  //Setters and Getters-------------------------------
  int size();
  double get(int i);
  void set(int i, double x);

  //Methods------------------------------------------
  double norm();
  double max();
  void display();
  void print(std::string namef);

  //Binary operators----------------------------------------
  friend point  operator+(const point  & v, const point  & w);
  friend point  operator-(const point  & v, const point  & w);
  friend point  operator*(const point  & v, const point  & w);
  friend point  operator*(const double & a, const point  & v);
  friend point  operator/(const point  & v, const double & a);
  friend double operator|(const point  & v, const point  & w);

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
