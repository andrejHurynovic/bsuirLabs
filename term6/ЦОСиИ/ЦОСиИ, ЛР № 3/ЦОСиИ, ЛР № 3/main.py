from cmath import exp
from math import pi, sin, cos, floor, trunc, log
import numpy as np
from scipy.fft import fft, ifft
import matplotlib.pyplot as plt
from numpy.random import rand

x = np.arange(0, 2*pi, 2*pi/32)
input_vector = [sin(5 * t) + cos(2 * t) for t in x]
plt.plot(input_vector)
plt.show()



from sympy import fwht

output1 = fwht(input_vector)
print("Transform  : ", output1)
plt.plot(output1)
plt.show()


def my_fwht(a):
    h = 1
    while h < len(a):
        for i in range(0, len(a), h * 2):
            for j in range(i, i + h):
                x = a[j]
                y = a[j + h]
                a[j] = x + y
                a[j + h] = x - y
        h *= 2
    return a


output2 = my_fwht(input_vector)
print(output2)
plt.plot(output2)
plt.show()

