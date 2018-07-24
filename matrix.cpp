#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
#include"matrix.h"

//Constructors----------------------------------------------------
matrix::matrix(const matrix & M): dimension(M.dimension){
  for(int i=0; i<dimension; i++){
    std::vector<double> line;
    for(int j=0; j<dimension; j++){
      line.push_back(M.values[i][j]);
    }
    values.push_back(line);
  }
}

matrix::matrix(int n): dimension(n){
  for(int i=0; i<dimension; i++){
    std::vector<double> line;
    for(int j=0; j<dimension; j++){
      line.push_back(0);
    }
    values.push_back(line);
  }
}

matrix::matrix(): dimension(3){
  for(int i=0; i<dimension; i++){
    std::vector<double> line;
    for(int j=0; j<dimension; j++){
      line.push_back(0);
    }
    values.push_back(line);
  }
  //for(int i=0; i<dimension; i++){
  //  values[i][i] = 1.;
  // }
}

matrix::matrix(double a, double b, double c): dimension(3){
  for(int i=0; i<dimension; i++){
    std::vector<double> line;
    for(int j=0; j<dimension; j++){
      line.push_back(0);
    }
    values.push_back(line);
  }
  values[0][0] = a;
  values[1][1] = b;
  values[2][2] = c; 
}


matrix::matrix(int n, double x): dimension(n){
  for(int i=0; i<dimension; i++){
    std::vector<double> line;
    for(int j=0; j<dimension; j++){
      line.push_back(x);
    }
    values.push_back(line);
  }
}

//Methods--------------------------------------------------------
int matrix::size(){
  return dimension;
}

void matrix::set(int i, int j, double x){
  values[i][j] = x;
}
double matrix::get(int i, int j){
  return values[i][j];
}

matrix matrix::transpose(){
  matrix M(dimension);
  for(int i=0; i<dimension; i++){
    for(int j=0; j<dimension; j++){
      M.set(i,j,values[j][i]);
    }
  }
  return M;
}

point matrix::act(point v){
  point w(dimension);
  for(int i=0; i<dimension; i++){
    double x = 0;
    for(int j=0; j<dimension; j++){
      x+= values[i][j]*v.get(j);
    }
    w.set(i,x);
  }
  return w;
}

void matrix::display(){
  for(int i=0; i<dimension; i++){
    for(int j=0; j<dimension; j++){
      std::cout << values[i][j] << '\t';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void matrix::diag3(double a, double b, double c){
  values[0][0] = a;values[1][1] = b;values[2][2] = c;
}


//Binary Operators-------------------------------------------
matrix operator+(const matrix & M, const matrix & N){
  int n = M.dimension;
  matrix P(n);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      P.set(i,j,M.values[i][j]+N.values[i][j]);
    }
  }
  return P;
}
matrix operator-(const matrix & M, const matrix & N){
  int n = M.dimension;
  matrix P(n);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      P.set(i,j,M.values[i][j]-N.values[i][j]);
    }
  }
  return P;
}

matrix operator*(const matrix & M, const matrix & N){
  int n = M.dimension;
  matrix P(n);
  double sum;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      sum = 0;
      for(int k=0; k<n; k++){
	sum+=M.values[i][k]*N.values[k][j];
      }
      P.set(i,j,sum);
    }
  }
  return P;
}

matrix operator*(const double & a, const matrix & M){
int n = M.dimension;
  matrix P(n);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      P.set(i,j,a*M.values[i][j]);
    }
  }
  return P;
}

matrix operator/(const matrix & M, const double & a){
int n = M.dimension;
  matrix P(n);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      P.set(i,j,M.values[i][j]/a);
    }
  }
  return P;
}

std::ostream& operator<<(std::ostream& os, const matrix& M){
  for(int i=0; i<M.dimension; i++){
    for(int j=0; j<M.dimension; j++){
      os << M.values[i][j] << '\t';
    }
    os << std::endl;
  }
  return os;
}

//Unitary Operators---------------------------------
matrix & matrix::operator+=(const matrix &M){
  for(int i=0; i<dimension; i++){
    for(int j=0; j<dimension; j++){
      values[i][j]+=M.values[i][j];
    }
  }
  return *this;
}
matrix & matrix::operator-=(const matrix &M){
  for(int i=0; i<dimension; i++){
    for(int j=0; j<dimension; j++){
      values[i][j]-=M.values[i][j];
    }
  }
  return *this;
}

matrix & matrix::operator*=(const matrix &M){
  matrix N(*this);
  int n = M.dimension;
  double sum;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      sum = 0;
      for(int k=0; k<n; k++){
	sum+=M.values[i][k]*N.values[k][j];
      }
      values[i][j] = sum;
    }
  }
  return *this;
}

matrix & matrix::operator=(const matrix &M){
  if(this!=&M){
    for(int i=0; i<dimension; i++){
      for(int j=0; j<dimension; j++){
	values[i][j] = M.values[i][j];
      }
    }
  }
  return *this;
}

matrix & matrix::operator/=(double x){
  for(int i=0; i<dimension; i++){
    for(int j=0; j<dimension; j++){
      values[i][j]/= x;
    }
  }
  return *this;
}
