# Particles-in-ABCflow

This is a project of simulation of the movement of little solid spheroids in an ABC-flow, using quaternions to describe the rotation of the elipsoid.
Here are a brief descritpion of each file:

What I call the tool files: point.h/cpp, matrix.h/cpp, quat.h/cpp.

"point" is a class decribing vectors, the closest possible to the mathematical object (the name vector is already taken by another standard class of C++, wich is only some kind of sofisticated array). It can be of any dimension, but by default, it is a vector of a 3D space. A bunch of functions are added, such as calculating the norm, of setting the value of each component. The usual symbols of operations are also overdefined to allow the addition betwen two points, the multiplication by a real number, the dot and cross product, and the operator << that allows the point to be prompted on screen or written in a file.

"matrix" is simply of class of matrix, wich need the point class to work. A number of classic function on matrix are defined, and also a function called act() wich simply take a object point to operate on it and return a point. Again, a matrix can be of any dimension, but is by default a 3D matrix.

"quaternion" in the quat.h/cpp files is a class describing quaternions. It depends on the classes point and matrix to work. As quaternions are used to described rations in a 3D space, it can be defined via an angle and an axis of rotation. However, as the mathematical components are different than these values, a quaternion can also used with the actual components of the mathematical object. It can act one an object point, as previously, but also produce a matrix of rotation. A function normalize() is also defined to set the norm of the quaternion to 1, as a rotation quaternion must be unitary.
