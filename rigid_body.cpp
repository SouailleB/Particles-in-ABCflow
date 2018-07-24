#include"point.h"
#include"matrix.h"
#include"quat.h"
#include"rigid_body.h"
#include<iostream>
#include<fstream>
#include<cmath>

void rigid_body::display(){
  std::cout << "Mass: " << mass << std::endl;
  std::cout << std::endl << "Angle Inerta:  " << std::endl;
  ang_inertia.display();
  std::cout << std::endl << "Position: ";
  position.display();
  std::cout << std::endl << "Orientatiion: ";
  orientation.display_aa();
  std::cout << std::endl << "Linear Momentum: ";
  lin_momentum.display();
  std::cout << std::endl << "Angular Momentum: ";
  ang_momentum.display();
  std::cout << std::endl;
}

void rb2array(rigid_body rb, double y[]){
  y[0] = rb.position.get(0);
  y[1] = rb.position.get(1);
  y[2] = rb.position.get(2);

  rb.orientation.normalize();
  
  y[3] = rb.orientation.get(0);
  y[4] = rb.orientation.get(1);
  y[5] = rb.orientation.get(2);
  y[6] = rb.orientation.get(3);
  
  y[7] = rb.lin_momentum.get(0);
  y[8] = rb.lin_momentum.get(1);
  y[9] = rb.lin_momentum.get(2);
    
  y[10] = rb.ang_momentum.get(0);
  y[11] = rb.ang_momentum.get(1);
  y[12] = rb.ang_momentum.get(2);    
}

void array2rb(rigid_body &rb, double y[]){
  rb.position.set(0,y[0]);
  rb.position.set(1,y[1]);
  rb.position.set(2,y[2]);

  rb.orientation.set(0,y[3]);
  rb.orientation.set(1,y[4]);
  rb.orientation.set(2,y[5]);
  rb.orientation.set(3,y[6]);

  rb.orientation.normalize();
  
  rb.lin_momentum.set(0,y[7]);
  rb.lin_momentum.set(1,y[8]);
  rb.lin_momentum.set(2,y[9]);

  rb.ang_momentum.set(0,y[10]);
  rb.ang_momentum.set(1,y[11]);
  rb.ang_momentum.set(2,y[12]);
}
