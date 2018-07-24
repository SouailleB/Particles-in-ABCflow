#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>
#include<random>
#include"point.h"
#include"matrix.h"
#include"quat.h"
#include"rigid_body.h"
#include"ode.h"
#include"model.h"

using namespace std;

#define AREA 2

random_device gen;
uniform_real_distribution<double> zone(-AREA,AREA);
uniform_real_distribution<double> angle(0,2*M_PI);
uniform_real_distribution<double> uni(-1,1);

point rand_unit_point();
point jeff_torque(point r,point omega);
//point drag_force(point r, quaternion q);

double a=1, b=3;
double lambda = b/a;
double mass = 0.5;
double Ia = (mass/5)*(a*a+b*b);
double Ib = (mass/5)*(2*a*a);

double delta = 1e-3;
point x_lab(1,0,0), y_lab(0,1,0), z_lab(0,0,1);
matrix inv_I,I;
point pos;
point lm;
point am;
point force, torque;
quaternion ori;

rigid_body grain;

double qa,qb,qc,qd,norm;
void normalize_quaternion(double y[]){
  qa = y[3];
  qb = y[4];
  qc = y[5];
  qd = y[6];
  norm = sqrt(qa*qa+qb*qb+qc*qc+qd*qd);
  y[3] = qa/norm;
  y[4] = qb/norm;
  y[5] = qc/norm;
  y[6] = qd/norm;  
}

void set_init_cond(double y[]){    
  I.diag3(Ia, Ia, Ib);
  inv_I.diag3(1/Ia, 1/Ia, 1/Ib);

  pos.set(0, zone(gen));
  pos.set(1, zone(gen));
  pos.set(2, zone(gen));
  
  ori.set_aa(angle(gen), rand_unit_point());

  cout << "Initial orientation : " << ori << endl;
  cout << "Initial position : "    << pos << endl;
  
  grain.mass = mass;
  grain.ang_inertia = I;
  grain.inv_ang_in = inv_I;
  grain.position = pos;
  grain.orientation = ori;
  grain.lin_momentum = lm;
  grain.ang_momentum = am;
  
  rb2array(grain, y);
}

quaternion dq_dt;
point dL_dt, omega;

int n = 0;
double mu = 1;

void eval_rhs(double time, double y[],double rhs[]){
  normalize_quaternion(y);
  array2rb(grain, y);
  omega = inv_I.act(grain.ang_momentum);
  
  //force = drag_force(grain.position, grain.orientation);
  torque_lab = jeff_torque(grain.position, grain.orientation.bff2lab(omega));
  /*
  if(n%4==0){
    //cout << a*flow(grain.position).norm()/mu << endl;
    cout << flow(grain.position) << endl;
    }
  */
  n++;
  
  dq_dt = 0.5*(grain.orientation*omega);
  dL_dt = grain.orientation.lab2bff(torque_lab)+(grain.ang_momentum*omega);
  
  rhs[0]= flow(grain.position).get(0);
  rhs[1]= flow(grain.position).get(1);
  rhs[2]= flow(grain.position).get(2);
  
  rhs[3]= dq_dt.get(0);
  rhs[4]= dq_dt.get(1);
  rhs[5]= dq_dt.get(2);
  rhs[6]= dq_dt.get(3);
  
  rhs[7]= force.get(0);
  rhs[8]= force.get(1);
  rhs[9]= force.get(2);
  
  rhs[10]= dL_dt.get(0);
  rhs[11]= dL_dt.get(1);
  rhs[12]= dL_dt.get(2);
}

matrix get_I_bff(){
  I.diag3(Ia,Ia,Ib);  
  return I;
}

matrix get_inv_I_bff(){
  inv_I.diag3(1/Ia, 1/Ia, 1/Ib);
  return inv_I;
}

double const Kxx = (16*M_PI*a*pow(lambda*lambda-1, 1.5))/((2*lambda*lambda-3)*log(lambda+sqrt(lambda*lambda-1))+lambda*sqrt(lambda*lambda-1));
 //Kxx= Kyy

double const Kzz = (8*M_PI*a*pow(lambda*lambda-1, 1.5))/((2*lambda*lambda-1)*log(lambda+sqrt(lambda*lambda-1))-lambda*sqrt(lambda*lambda-1));

matrix const K(mu*Kxx, mu*Kxx, mu*Kzz);

/*
point drag_force(point r, quaternion q){
  matrix R,Rt;
  R  = q.rot_mat();
  Rt = (q.conjugate()).rot_mat();
  
  return ((Rt*K)*R).act(flow(r)); //viscosity included in K, see above
}
*/


double q = sqrt(b*b-a*a);
double betha = log((b+q)/(b-q))/pow(q,3)-2/(q*q*b);
double alpha = 0.5*log((b-q)/(b+q))/pow(q,3)+b/(a*a*q*q);

double const Cx=(16*mu*M_PI*pow(a,3)*lambda)/(3*(alpha+lambda*lambda*betha));
  //Cy=Cx;
double const Cz=(16*mu*M_PI*pow(a,3)*lambda)/(3*alpha);

point jeff_torque(point r, point omega){
  double Gamma_x, Gamma_y, Gamma_z;
  point Gamma;
  point Omega;
  matrix Sij;
  
  Omega = antisym_part(r);
  Sij = sym_part(r);
  
  Gamma_x=Cx*((1-lambda*lambda)*Sij.get(1,2)+(1+lambda*lambda)*((Omega-omega).get(0)));
  Gamma_y=Cx*((lambda*lambda-1)*Sij.get(0,2)+(1+lambda*lambda)*((Omega-omega).get(1)));
  Gamma_z=Cz*((Omega-omega).get(2));
  
  Gamma.set(0, Gamma_x);
  Gamma.set(1, Gamma_y);
  Gamma.set(2, Gamma_z);
  return Gamma;
}

point rand_unit_point(){
  point v(uni(gen), uni(gen), uni(gen));
  v = v/v.norm();
  return v;
}
