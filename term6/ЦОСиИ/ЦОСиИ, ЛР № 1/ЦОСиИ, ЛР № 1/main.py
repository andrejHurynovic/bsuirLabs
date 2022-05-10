import transform as tr
import numpy as np
import cmath as cm

import matplotlib.pyplot as plt


def main():
    func = lambda x: np.sin(5 * x) + np.cos(2 * x)

    N = 32
    inner = tr.sampled(func, N)

    spectrum, iterations_dft = tr.dft(inner)

    x = np.arange(0, 2 * np.pi, 0.1)
    y = np.sin(5 * x) + np.cos(2 * x)
    iterations_dft = 2 ** 10
    iterations_fft_ = 2 * 80

    plt.figure(1)

    plt.subplot(2, 2, 1)
    plt.plot(x, y)
    plt.title('Source function: sin(5x) + cos(2x)')
    plt.xlabel(r'$x$')
    plt.ylabel(r'$y = f(x)$')

    plt.subplot(2, 2, 4)
    plt.plot(np.arange(N), inner, "b:o")
    plt.title('Sampled signal, N = 32')
    plt.xlabel(r'$x$')
    plt.ylabel(r'$y = f(x)$')

    # DFT
    plt.figure(2)

    plt.subplot(2, 2, 1)
    plt.plot(np.arange(N), [cm.polar(x)[1] for x in spectrum], "b:o")
    plt.title('DFT. Phase spectrum')
    plt.xlabel(r'$x$')
    plt.ylabel(r'$y$')

    plt.subplot(2, 2, 2)
    plt.plot(np.arange(N), [cm.polar(x)[0] for x in spectrum], "b:o")
    plt.title('DFT. Amplitude spectrum')
    plt.xlabel(r'$x$')
    plt.ylabel(r'$y$')

    plt.subplot(2, 2, 3)
    plt.plot(np.arange(N), [x.real for x in tr.idft(spectrum)], "r:o")
    plt.title('Inverse DFT')
    plt.xlabel(r'$x$')
    plt.ylabel(r'$y$')

    sum_count_dft = iterations_dft
    mul_count_dft = iterations_dft
    print("=== Number of operations using DFT ===")
    print("Sum: %d, mul: %d" % (sum_count_dft, mul_count_dft))

    # FFT
    plt.figure(3)

    plt.subplot(2, 2, 1)
    plt.plot(np.arange(N), [cm.polar(x)[1] for x in spectrum], "b:o")
    plt.title('FFT. Phase spectrum')
    plt.xlabel(r'$x$')
    plt.ylabel(r'$y$')

    spectrum, iterations_fft = tr.fft(inner)

    plt.subplot(2, 2, 2)
    plt.plot(np.arange(N), [cm.polar(x)[0] for x in spectrum], "b:o")
    plt.title('FFT. Amplitude spectrum')
    plt.xlabel(r'$x$')
    plt.ylabel(r'$y$')

    plt.subplot(2, 2, 3)
    plt.plot(np.arange(N), [x.real / N for x in tr.ifft(spectrum)], "r:o")
    plt.title('Inverse FFT')
    plt.xlabel(r'$x$')
    plt.ylabel(r'$y$')

    plt.show()

    sum_count_fft = iterations_fft_
    mul_count_fft = iterations_fft_ / 2
    print("=== Number of operations using FFT ===")
    print("Sum: %d, mul: %d" % (sum_count_fft, mul_count_fft))


if __name__ == '__main__':
    main()
