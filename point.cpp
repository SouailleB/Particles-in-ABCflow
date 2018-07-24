#include<vector>
#include<fstream>
#include<cmath>
#include"point.h"
#define MAX(a,b) (((a)>(b))? (a) : (b))

//Constructors-------------------------------------
point::point(){
  dimension = 3;
  for(int i=0; i<3; i++){
    values.push_back(0.);
  }
}

point::point(double x, double y, double z){
  dimension = 3;
  values.push_back(x);
  values.push_back(y);
  values.push_back(z);
}

point::point(const point& v):dimension(v.dimension){
  for(int i=0; i<v.dimension; i++){
    values.push_back(v.values[i]);
  }
}

point::point(int n) : dimension(n){
  for(int i=0; i<n; i++){
    values.push_back(0.);
  }
}

point::point(int n, double x) : dimension(n){
  for(int i=0; i<n; i++){
    values.push_back(x);
  }
}

//Setters and Getters------------------------------
int point::size(){
  return dimension;
}
double point::norm(){
  double sum = 0;
  for(int i = 0; i<dimension; i++){
    sum += values[i]*values[i];
  }
  return sqrt(sum);
}

double point::get(int i){
  return values[i];
}

void point::set(int i, double x){
  values[i] = x;
}


//Methods-----------------------------------------
void point::display(){
  for(int i=0; i<dimension; i++){
    std::cout << values[i] << "  ";
  }
  std::cout << std::endl;
}

void point::print(std::string namef){
  std::fstream file;
  file.open(namef, std::ios::out);
  for(int i=0; i<dimension; i++){
    file << 0. << "    ";
  }
  for(int i=0; i<dimension; i++){
    file << values[i] << "    ";
  }
  file << std::endl;
  file.close();
}

//Binary operators--------------------------------
point operator+(const point & v, const point & w){
  int n = v.dimension;
  point u(n);
  for(int i=0; i<n; i++){
    u.values[i] = v.values[i]+w.values[i];
  }
  return u;
}
point operator-(const point & v, const point & w){
  int n = v.dimension;
  point u(n);
  for(int i=0; i<n; i++){
    u.values[i] = v.values[i]-w.values[i];
  }
  return u;
}

point operator*(const point & v, const point & w){
  point u(3);

  u.values[0] = v.values[1]*w.values[2]-v.values[2]*w.values[1];
  u.values[1] = v.values[2]*w.values[0]-v.values[0]*w.values[2];
  u.values[2] = v.values[0]*w.values[1]-v.values[1]*w.values[0];
  
  return u;
}

point operator*(const double & a, const point & v){
  int n = v.dimension;
  point u(n);
  for(int i=0; i<n; i++){
    u.values[i] = a*v.values[i];
  }
  return u;
}

point operator/(const point & v, const double & a){
  int n = v.dimension;
  point u(n);
  for(int i=0; i<n; i++){
    u.values[i] = v.values[i]/a;
  }
  return u;
}

double operator|(const point & v, const point & w){
  int n = v.dimension;
  double sum = 0;
  for(int i=0; i<n; i++){
    sum+=v.values[i]*w.values[i];
  }
  return sum;
}

std::ostream& operator<<(std::ostream& os, const point& v){
  for(int i=0; i<v.dimension-1; i++){
    os << v.values[i] << '\t';
  }
  os << v.values[v.dimension-1];
  return os;
}

//Unitary operators--------------------------------
point &  point::operator=(const point & v){
  if(&v!=this){
    dimension = v.dimension;
    for(int i=0; i<dimension; i++){
      values[i]=v.values[i];
    }
  }
  return *this;
}

point & point::operator+=(const point & v){
  if(&v!=this){
    for(int i=0; i<dimension; i++){
      values[i]+=v.values[i];
    }
  }
  return *this;
}

point & point::operator-=(const point & v){
  if(&v!=this){
    for(int i=0; i<dimension; i++){
      values[i]-=v.values[i];
    }
  }
  return *this;
}

point & point::operator*=(const double & a){
  for(int i=0; i<dimension; i++){
    values[i]*=a;
  }
  return *this;
}

point & point::operator/=(const double & a){
  for(int i=0; i<dimension; i++){
    values[i]/=a;
  }
  return *this;
}
