import numpy as np


# dif fft implementation
class FourierTransform:
    complexity_counter = 0

    @classmethod
    def fft(cls, input_data, input_length, direction=1):
        fft_result = cls._dif_fft(input_data, input_length, direction)

        if direction == -1:
            for i in range(input_length):
                fft_result[i] /= input_length

        return fft_result

    @classmethod
    def _dif_fft(cls, input_data, input_length, direction=1):
        if cls._is_power_of_two(input_length):
            length = input_length
            bits_in_length = int(np.log2(length))
        else:
            bits_in_length = np.log2(input_length)
            length = 1 << bits_in_length

        data = list(map(complex, input_data[:length]))

        cls.complexity_counter = 0

        for ldm in range(bits_in_length, 0, -1):
            m = 2 ** ldm
            mh = int(m / 2)
            for k in range(mh):
                w = np.exp(direction * -2j * np.pi * k / m)
                for r in range(0, length, m):
                    u = data[r + k]
                    v = data[r + k + mh]

                    data[r + k] = u + v
                    data[r + k + mh] = (u - v) * w

                    cls.complexity_counter += 1

        for i in range(length):
            j = cls._reverse_bits(i, bits_in_length)
            if j > i:
                temp = data[j]
                data[j] = data[i]
                data[i] = temp

        return data

    @staticmethod
    def fft_shift(fft_result):
        length = len(fft_result)

        first_half = fft_result[0:int(length / 2)]
        second_half = first_half[:]
        first_half.reverse()
        shifted_result = first_half + second_half

        return shifted_result

    @staticmethod
    def normalize_transform(fft_result, length):
        return list(np.divide(fft_result, length))

    @staticmethod
    def _is_power_of_two(n):
        return n > 1 and (n & (n - 1)) == 0

    @staticmethod
    def _reverse_bits(n, bits_count):
        reversed_value = 0

        for i in range(bits_count):
            next_bit = n & 1
            n >>= 1

            reversed_value <<= 1
            reversed_value |= next_bit

        return reversed_value