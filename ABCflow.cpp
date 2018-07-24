#include<fstream>
#include<cmath>
#include"point.h"
#include"matrix.h"
#include"model.h"

using namespace std;

#define COEF 1

double Sxy, Sxz, Syz;
double const kk = 5;
double const A=COEF, B=COEF, C=COEF;

point flow(point r){
  point u;
  u.set(0, A*cos(kk*r.get(2))+C*sin(kk*r.get(1)));
  u.set(1, B*cos(kk*r.get(0))+A*sin(kk*r.get(2)));
  u.set(2, C*cos(kk*r.get(1))+B*sin(kk*r.get(0)));
  return u;
}

matrix sym_part(point r){
  matrix Sij;
  
  Sxy = -C*kk*sin(kk*r.get(1))+B*kk*cos(kk*r.get(0));
  Sxz = -B*kk*sin(kk*r.get(0))+A*kk*cos(kk*r.get(2));
  Syz = -A*kk*sin(kk*r.get(2))+C*kk*cos(kk*r.get(1));
  
  Sij.set(0,1,  Sxy);
  Sij.set(1,0,  Sxy);

  Sij.set(0,2,  Sxz);
  Sij.set(2,0,  Sxz);

  Sij.set(0,1,  Syz);
  Sij.set(1,0,  Syz);

  return Sij;
}

point antisym_part(point r){
  point u(flow(r)); //ABCflow:  del u = kk*u
  return 0.5*kk*u;
}

/*
int main(){
  fstream flow_dat;
  flow_dat.open("ABCflow.txt", ios::out);
  
  point r;
  double scale = 0.5;
  int nb_vectors = 100;
  double size = 3;
  for(double x = -size; x <= size; x+=size/nb_vectors){
    for(double y = -size; y <= size; y+=size/nb_vectors){
      for(double z = -size; z <= size; z+=size/nb_vectors){
	r.set(0, x);
	r.set(1, y);
	r.set(2, z);
	flow_dat << r << '\t' << flow(r) << endl;
      }
    }
  }
  return 0;
}
*/
