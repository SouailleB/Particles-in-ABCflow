# Particles-in-ABCflow

This is a project of simulation of the movement of little solid spheroids in an ABC-flow, using quaternions to describe the rotation of the elipsoid.
Here are a brief descritpion of each file:

What I call the tool files: point.h/cpp, matrix.h/cpp, quat.h/cpp.

"point" is a class decribing vectors, the closest possible to the mathematical object (the name vector is already taken by another standard class of C++, wich is only some kind of sofisticated array). It can be of any dimension, but by default, it is a vector of a 3D space. A bunch of functions are added, such as calculating the norm, of setting the value of each component. The usual symbols of operations are also overdefined to allow the addition betwen two points, the multiplication by a real number, the dot and cross product, and the operator << that allows the point to be prompted on screen or written in a file.

"matrix" is simply of class of matrix, wich need the point class to work. A number of classic function on matrix are defined, and also a function called act() wich simply take a object point to operate on it and return a point. Again, a matrix can be of any dimension, but is by default a 3D matrix.

"quaternion" in the quat.h/cpp files is a class describing quaternions. It depends on the classes point and matrix to work. As quaternions are used to described rations in a 3D space, it can be defined via an angle and an axis of rotation. However, as the mathematical components are different than these values, a quaternion can also used with the actual components of the mathematical object. It can act one an object point, as previously, but also produce a matrix of rotation. A function normalize() is also defined to set the norm of the quaternion to one, as a rotation quaternion must be unitary.

In our problem, the flow simulated is an ABC-flow, written in the ABCflow.cpp file. It contains all the functions needed is the simulation.

Then, there is the rigid_body structure, wich is only a set of the main parameters of the spheroid. In addition, there are two functions used to convert this structure to an array (and conversly), that is necessary to the differential equation solver.

The ODE solver is written in the ode.h/cpp files. It handles one step of the RK4 solver. However, another function called eval_rhs() is declared, but not defined in the ode.cpp. It the function f(x) in the dx/dt = f(x) differential equation, determined by the problem at hand.

In our case, this function is defined in the model.cpp file, wich regroup all the physical aspect of our problem: definition of a rigid body, definition of the eval_rhs function, the call to the functions declared in ABCflow, and so on.

Finally, the main.cpp handles the calculation aspect of the problem, and calls everything declared in the model.cpp, to run the simulation with the defined parameters. It is also here that the results are written on some files.

plot.py is a template of python programm to print some 3D figures using matplotlib, based on the format I used one the output files. It can be modified easily.
