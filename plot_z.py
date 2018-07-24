from math import *
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def str2list(string) :
    result = []
    line = []
    number = ""
    x = 0.
    for element in string:
        if element == '\n':
            if number != "":
                x = float(number)
                line.append(x)
            result.append(line)
            number = ""
            line = []
        elif element == '\t':
            if number != "":
                x = float(number)
                line.append(x)
            number = ""
        else:
            number +=element
    return result
                
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

f = open('z_lab.txt','r')
data = f.read()
L = str2list(data)

X = [L[i][0] for i in range(len(L))]
Y = [L[i][1] for i in range(len(L))]
Z = [L[i][2] for i in range(len(L))]
"""
X = [1 for i in range(len(L))]
Y = [1 for i in range(len(L))]
Z = [1 for i in range(len(L))]
"""

norm = [L[i][3] for i in range(len(L))]
time = [i for i in range(len(L))]

plt.xlabel('x')
plt.ylabel('y')
#plt.zlabel('z')

plt.legend()
plt.plot(X,Y,Z)
plt.plot(X[0:2], Y[0:2], Z[0:2], 'r')
plt.show()
"""
plt.plot(time, norm)
plt.show()
"""
