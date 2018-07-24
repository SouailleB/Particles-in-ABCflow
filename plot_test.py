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

f = open('test.txt','r')
data = f.read()
L = str2list(data)

XL = [L[i][0] for i in range(len(L))]
YL = [L[i][1] for i in range(len(L))]
ZL = [L[i][2] for i in range(len(L))]

norm = [L[i][3] for i in range(len(L))]
time = [i for i in range(len(L))]

plt.xlabel('x')
plt.ylabel('y')
#plt.zlabel('z')

plt.legend()
plt.plot(XL,YL,ZL)
plt.plot(XL[0:2], YL[0:2], ZL[0:2], 'r')
plt.show()
plt.plot(time, norm)
plt.show()

