#include "device_launch_parameters.h"
#include "cuda_runtime.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

void cpu_function(int* first, int* second, int n, int m) {
    for (int temp = 0; temp < (m - m % 2) * (n - n % 2); temp++) {

        
        int i = temp / ((n / 2));
        int j = temp % ((n / 2));

        if (temp > (m - m % 2) * (n - n % 2)) continue;

        if (i % 4 == 0) {
            second[i * n / 2 + j] = first[(i / 2) * n + n + j * 2 + 1];
        }

        if (i % 4 == 1) {
            second[i * n / 2 + j] = first[(i / 2) * n + n + j * 2];
        }

        if (i % 4 == 2) {
            second[i * n / 2 + j] = first[(i / 4) * (n * 2) + j * 2 + 1];
        }

        if (i % 4 == 3) {
            second[i * n / 2 + j] = first[(i / 4) * (n * 2) + j * 2];
        }

    }
}


__global__ void gpu_function(int* first, int* second, int num_thread, int n, int m) {

    int temp = threadIdx.x + blockIdx.x * num_thread;

    int i = temp / ((n / 2));
    int j = temp % ((n / 2));

    if (temp > (m - m % 2) * (n - n % 2));

    else {
        if (i % 4 == 0) {
            second[i * n / 2 + j] = first[(i / 2) * n + n + j * 2 + 1];
        }
        if (i % 4 == 1) {
            second[i * n / 2 + j] = first[(i / 2) * n + n + j * 2];
        }
        if (i % 4 == 2) {
            second[i * n / 2 + j] = first[(i / 4) * (n * 2) + j * 2 + 1];
        }
        if (i % 4 == 3) {
            second[i * n / 2 + j] = first[(i / 4) * (n * 2) + j * 2];
        }
    }
}



int main(void) {

    int n = 10000;
    int m = 10000;
    int lenght = n * m;

    int* first;
    int* second;
    int* check_second;

    int* d_first;
    int* d_second;

    first = (int*)malloc(lenght * sizeof(int));
    second = (int*)malloc(lenght * sizeof(int));
    check_second = (int*)malloc(lenght * sizeof(int));

    for (int i = 0; i < lenght; i++) {
        first[i] = i;
    }

    for (int i = 0; i < lenght; i++) {
        second[i] = -1;
    }

    for (int i = 0; i < lenght; i++) {
        check_second[i] = -1;
    }

    cout << "\n";

    dim3 blocks((lenght / 32), 1);

    cudaMalloc((int**)&d_first, lenght * sizeof(int));
    cudaMalloc((int**)&d_second, lenght * sizeof(int));

    cudaMemcpy(d_first, first, lenght * sizeof(int), cudaMemcpyHostToDevice);

    cudaStream_t stream0;
    cudaStreamCreate(&stream0);

    cudaEvent_t e_start, e_stop;
    cudaEventCreate(&e_start);
    cudaEventCreate(&e_stop);
    cudaEventRecord(e_start, 0);


    gpu_function <<< blocks, 32, 0, stream0 >>> (d_first, d_second, 32, n, m);

    cudaDeviceSynchronize();
    cudaStreamSynchronize(stream0);

    cudaEventRecord(e_stop, 0);
    cudaEventSynchronize(e_stop);
    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime, e_start, e_stop);

    cout << "GPU time: " << elapsedTime << "ms" << endl;

 
    cudaMemcpy(check_second, d_second, lenght * sizeof(int), cudaMemcpyDeviceToHost);
    

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    cpu_function(first, second, n, m);

    auto stop = high_resolution_clock::now();
    duration<double> time = stop - start;
    cout << "CPU time: " << time.count() * 1000 << "ms" << endl;


    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout.fill(' ');
            cout.width(3);
            cout << setw(5) << check_second[i * n / 2 + j] << "  ";
        }
        cout << "\n";
    }
    cout << "\n";

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout.fill(' ');
            cout.width(3);
            cout << setw(5) << second[i * n / 2 + j] << "  ";
        }
        cout << "\n";
    }
    cout << "\n";


    for (int i = 0; i < (m / 2) * 4; i++) {
        for (int j = 0; j < n / 2; j++) {
            if (second[i * n / 2 + j] != check_second[i * n / 2 + j]) {
                cout << "\nfalse\n" << i << ' ' << j;
                //return;
            }
        }
    }


    cout << "\ntrue\n";
}