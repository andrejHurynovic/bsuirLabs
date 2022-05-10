import cmath
import numpy as np


def dft(inner):
    out = []
    iterations = (0, 0)
    length = len(inner)

    for m in range(length):
        temp = complex(.0, .0)
        for n in range(length):
            arg = -2 * np.pi * m * n / length
            temp = temp + complex(inner[n] * np.cos(arg), inner[n] * np.sin(arg))
            iterations = (iterations[0] + 2, iterations[1] + 2)

        out.append(temp)

    return out, iterations


def idft(inner):
    out = []
    length = len(inner)

    for m in range(length):
        temp = complex(.0, .0)
        for n in range(length):
            arg = 2 * cmath.pi * m * n / length
            temp = temp + complex(inner[n] * np.cos(arg), inner[n] * np.sin(arg))

        out.append(temp / length)

    return out


def _w(k, n):
    if k % n == 0:
        return 1
    arg = -2 * cmath.pi * k / n
    return complex(np.cos(arg), np.sin(arg))


def fft(inner, iterations=(0, 0)):
    out = []
    length = len(inner)

    if length == 2:
        out.append(inner[0] + inner[1])
        out.append(inner[0] - inner[1])
        iterations = (iterations[0] + 2, iterations[1])

    else:
        even = [inner[x] for x in range(0, len(inner), 2)]
        odd = [inner[x] for x in range(1, len(inner), 2)]

        even, iterations = fft(even, iterations)
        odd, iterations = fft(odd, iterations)

        out = [None] * length
        for i in range(0, int(length / 2)):
            out[i] = even[i] + _w(i, length) * odd[i]
            out[i + int(length / 2)] = even[i] - _w(i, length) * odd[i]
            iterations = (iterations[0] + 1, iterations[1] + 2)

    return out, iterations


def ifft(inner):
    length = len(inner)
    out = []

    if length == 2:
        out.append(complex(inner[0] + inner[1]))
        out.append(complex(inner[0] - inner[1]))

    else:
        even = [inner[x] for x in range(0, len(inner), 2)]
        odd = [inner[x] for x in range(1, len(inner), 2)]

        even = ifft(even)
        odd = ifft(odd)

        out = [None] * length
        for i in range(0, int(length / 2)):
            out[i] = even[i] + _w(i, length).conjugate() * odd[i]
            out[i + int(length / 2)] = even[i] - _w(i, length).conjugate() * odd[i]

    return out


def sampled(func, n, period=(2 * cmath.pi)):
    out = []
    for i in range(n):
        out.append(func(period * (i + 1) / n))

    return out
