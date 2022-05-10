from operations import SignalProcessor
import numpy as np
import matplotlib.pyplot as plt


def main():
    n = 8
    arguments = np.arange(0, n) * np.pi / 6
    function_values_1 = list(map(lambda x: np.cos(2 * x), arguments))
    function_values_2 = list(map(lambda x: np.sin(5 * x), arguments))

    basic_correlation = SignalProcessor.correlation_convolution(function_values_1, function_values_2, 1)
    print('Basic correlation complexity: {}'.format(SignalProcessor.complexity_counter))
    basic_convolution = SignalProcessor.correlation_convolution(function_values_1, function_values_2, -1)
    print('Basic convolution complexity: {}'.format(SignalProcessor.complexity_counter))

    fft_based_correlation = \
        SignalProcessor.correlation_convolution_fft_based(function_values_1, function_values_2, 1)
    print('FFT-based correlation complexity: {}'.format(SignalProcessor.complexity_counter))
    fft_based_convolution = \
        SignalProcessor.correlation_convolution_fft_based(function_values_1, function_values_2, -1)
    print('FFT-based convolution complexity: {}'.format(SignalProcessor.complexity_counter))

    _, ((ax1, ax2), (ax3, ax4), (ax5, ax6)) = plt.subplots(3, 2)

    ax1.plot(arguments, function_values_1)
    ax1.set(title='cos(2x)')
    ax1.grid()

    ax2.plot(arguments, function_values_2)
    ax2.set(title='sin(5x)')
    ax2.grid()

    ax3.plot(arguments, basic_correlation)
    ax3.set(title='CORR')
    ax3.grid()

    ax4.plot(arguments, basic_convolution)
    ax4.set(title='CONV')
    ax4.grid()

    ax5.plot(arguments, fft_based_correlation)
    ax5.set(title='FFT-CORR')
    ax5.grid()

    ax6.plot(arguments, fft_based_convolution)
    ax6.set(title='FFT-CONV')
    ax6.grid()

    plt.show()


if __name__ == '__main__':
    main()
