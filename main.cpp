#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>
#include"point.h"
#include"matrix.h"
#include"quat.h"
#include"rigid_body.h"
#include"ode.h"
#include"model.h"

using namespace std;

#define NB_PARA 13
#define TIME_MAX 1
#define STEP 1e-3
#define PRECISION 5

double   Y[NB_PARA];
double rhs[NB_PARA];

int main(){
  set_init_cond(Y);
  
  fstream data;
  data.open("all_data.txt", ios::out);
  data.precision(PRECISION);
  fstream traj_data;
  traj_data.open("trajectory.txt", ios::out);
  traj_data.precision(PRECISION);  
  
  fstream bff_dat;
  bff_dat.open("bff_dat.txt", ios::out);
  bff_dat.precision(PRECISION);
  fstream lab_dat;
  lab_dat.open("lab_dat.txt", ios::out);
  lab_dat.precision(PRECISION);
  
  double time=0;
  
  data<<"time"<<'\t'<<"X"<<'\t'<<"Y"<<'\t'<<"Z"<<'\t'<<"Qw"<<'\t'<<"Qx"<<'\t'<< "Qy" << '\t'<<"Qz"<<'\t'<<"Px"<<'\t'<<"Py"<<'\t'<<"Pz"<<'\t'<< "Lx"<<'\t'<<"Ly"<<'\t'<<"Lz"<<'\t'<< endl;
  
  point z(0,0,1), z_lab;
  point position;
  point omega, omega_lab;
  point L, L_lab;
  quaternion ori;
  matrix I, I_lab, inv_I, inv_I_lab, R_q, R_qb;
  inv_I = get_inv_I_bff();
  I = get_I_bff();
  double step = STEP;
  
  while(time<=TIME_MAX){
    data << time << '\t';
    for(int i=0; i<NB_PARA; i++){
      data << Y[i] << '\t';
    }
    data << endl;
    
    position.set(0,Y[0]);
    position.set(1,Y[1]);
    position.set(2,Y[2]);
    
    traj_data << position << '\t' << flow(position) << endl;
    
    L.set(0, Y[10]);
    L.set(1, Y[11]);
    L.set(2, Y[12]);
    
    ori.set(0, Y[3]);
    ori.set(1, Y[4]);
    ori.set(2, Y[5]);
    ori.set(3, Y[6]);
    
    L_lab = ori.bff2lab(L);
    omega = inv_I.act(L);    
    omega_lab = ori.bff2lab(omega);
    
    double LL = L.norm();
    double LL_lab = L_lab.norm();
    
    double oo = omega.norm();
    double oo_lab = omega_lab.norm();
    
    bff_dat << L << '\t' << LL << '\t';
    bff_dat << omega << '\t' << oo << endl;
    lab_dat <<  L_lab << '\t' << LL_lab << '\t';
    lab_dat << omega_lab << '\t' << oo_lab << endl;
    
    rnkt4(NB_PARA, Y, time, step);
    //euler(NB_PARA, Y, time, step);
    normalize_quaternion(Y);
    time+=step;
  }    
  data.close();
  bff_dat.close();
  lab_dat.close();
  traj_data.close();
  return 0;
}
