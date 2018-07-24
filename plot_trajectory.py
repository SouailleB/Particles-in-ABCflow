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

def printl(L):
    for i in range(len(L)):
        print(L[i], '\n')

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

f = open('trajectory.txt','r')
data = f.read()
L = str2list(data)

XL = [L[i][0] for i in range(len(L))]
YL = [L[i][1] for i in range(len(L))]
ZL = [L[i][2] for i in range(len(L))]

VXL = [L[i][3] for i in range(len(L))]
VYL = [L[i][4] for i in range(len(L))]
VZL = [L[i][5] for i in range(len(L))]


plt.xlabel('x')
plt.ylabel('y')
#plt.zlabel('z')
plt.legend()
plt.plot(XL,YL,ZL)
plt.plot(XL[0:2], YL[0:2], ZL[0:2], 'r')

plt.show()
"""
plt.legend()
plt.plot([0],[0],[0])
plt.plot(VXL,VYL,VZL)
plt.plot(VXL[0:2], VYL[0:2], VZL[0:2], 'r')

plt.show()
"""
