#ifndef MATRIX_H
#define MATRIX_H

//point.h include already everything needed
#include"point.h"
#include<vector>

class matrix{
 public:
  //Constructors--------------------------------------------------
  matrix(const matrix & M);
  matrix();
  matrix(int n);
  matrix(int n, double x);
  matrix(double a, double b, double c);
  
  //Methods-------------------------------------------------------
  int size();
  void set(int i, int j, double x);
  double get(int i, int j);
    
  matrix transpose();
  point act(point v);
  void display();
  void diag3(double a, double b, double c);
  
  //Binary Operators------------------------------------------------
  friend matrix operator+(const matrix & M, const matrix & N);
  friend matrix operator-(const matrix & M, const matrix & N);
  friend matrix operator*(const matrix & M, const matrix & N);
  friend matrix operator*(const double & a, const matrix & M);
  friend matrix operator/(const matrix & M, const double & a);
  friend std::ostream& operator<<(std::ostream& os, const matrix& M);
  
  //Unitary Operators-----------------------------------------------
  matrix & operator=(const matrix &M);
  matrix & operator+=(const matrix &M);
  matrix & operator-=(const matrix &M);
  matrix & operator*=(const matrix &M);
  matrix & operator*=(double x);
  matrix & operator/=(double x);
  
 private:
  std::vector<std::vector<double>> values;
  int dimension;
};

#endif
