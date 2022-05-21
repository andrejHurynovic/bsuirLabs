
#include <device_functions.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "curand.h"
#include "curand_kernel.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNELS 3
#define WINDOW_SIZE 3
#define TILE_SIZE 15

#define CUDA_CALL(x) do { if((x)!=cudaSuccess) { \
    printf("Error at %s:%d\n %s",__FILE__,__LINE__, cudaGetErrorString(x));\
    exit(EXIT_FAILURE);}} while(0)
#define CURAND_CALL(x) do { if((x)!=CURAND_STATUS_SUCCESS) { \
    printf("Error at %s:%d\n",__FILE__,__LINE__);\
    exit(EXIT_FAILURE);}} while(0)

typedef std::chrono::high_resolution_clock ttime;
typedef ttime::time_point time_point;
#define DURATION(x) std::chrono::duration_cast<std::chrono::microseconds>(ttime::now() - x).count()


__device__ __inline__ void Sort(int& a, int& b)
{
	const int d = a - b;
	const int m = ~(d >> 8);
	b += d & m;
	a -= d & m;
}

__global__ void medianFilterSharedKernel(unsigned char* inputImageKernel, unsigned char* outputImagekernel, int imageWidth, int imageHeight)
{
	//Set the row and col value for each thread.
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	//printf("\n%d", row);
	__shared__ unsigned char sharedmem[(TILE_SIZE + 2)][(TILE_SIZE + 2)];  //initialize shared memory
	//Take some values.
	bool is_x_left = (threadIdx.x == 0), is_x_right = (threadIdx.x == TILE_SIZE - 1);
	bool is_y_top = (threadIdx.y == 0), is_y_bottom = (threadIdx.y == TILE_SIZE - 1);

	//Initialize with zero
	if (is_x_left)
		sharedmem[threadIdx.x][threadIdx.y + 1] = 0;
	else if (is_x_right)
		sharedmem[threadIdx.x + 2][threadIdx.y + 1] = 0;
	if (is_y_top) {
		sharedmem[threadIdx.x + 1][threadIdx.y] = 0;
		if (is_x_left)
			sharedmem[threadIdx.x][threadIdx.y] = 0;
		else if (is_x_right)
			sharedmem[threadIdx.x + 2][threadIdx.y] = 0;
	}
	else if (is_y_bottom) {
		sharedmem[threadIdx.x + 1][threadIdx.y + 2] = 0;
		if (is_x_right)
			sharedmem[threadIdx.x + 2][threadIdx.y + 2] = 0;
		else if (is_x_left)
			sharedmem[threadIdx.x][threadIdx.y + 2] = 0;
	}

	//Setup pixel values
	sharedmem[threadIdx.x + 1][threadIdx.y + 1] = inputImageKernel[row * imageWidth + col];
	//Check for boundry conditions.
	if (is_x_left && (col > 0))
		sharedmem[threadIdx.x][threadIdx.y + 1] = inputImageKernel[row * imageWidth + (col - 1)];
	else if (is_x_right && (col < imageWidth - 1))
		sharedmem[threadIdx.x + 2][threadIdx.y + 1] = inputImageKernel[row * imageWidth + (col + 1)];
	if (is_y_top && (row > 0)) {
		sharedmem[threadIdx.x + 1][threadIdx.y] = inputImageKernel[(row - 1) * imageWidth + col];
		if (is_x_left)
			sharedmem[threadIdx.x][threadIdx.y] = inputImageKernel[(row - 1) * imageWidth + (col - 1)];
		else if (is_x_right)
			sharedmem[threadIdx.x + 2][threadIdx.y] = inputImageKernel[(row - 1) * imageWidth + (col + 1)];
	}
	else if (is_y_bottom && (row < imageHeight - 1)) {
		sharedmem[threadIdx.x + 1][threadIdx.y + 2] = inputImageKernel[(row + 1) * imageWidth + col];
		if (is_x_right)
			sharedmem[threadIdx.x + 2][threadIdx.y + 2] = inputImageKernel[(row + 1) * imageWidth + (col + 1)];
		else if (is_x_left)
			sharedmem[threadIdx.x][threadIdx.y + 2] = inputImageKernel[(row + 1) * imageWidth + (col - 1)];
	}

	__syncthreads();   //Wait for all threads to be done.

	//Setup the filter.
	int a[9] = { sharedmem[threadIdx.x][threadIdx.y], sharedmem[threadIdx.x + 1][threadIdx.y], sharedmem[threadIdx.x + 2][threadIdx.y],
				  sharedmem[threadIdx.x][threadIdx.y + 1], sharedmem[threadIdx.x + 1][threadIdx.y + 1], sharedmem[threadIdx.x + 2][threadIdx.y + 1],
				  sharedmem[threadIdx.x][threadIdx.y + 2], sharedmem[threadIdx.x + 1][threadIdx.y + 2], sharedmem[threadIdx.x + 2][threadIdx.y + 2] };

	Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]);
	Sort(a[0], a[1]); Sort(a[3], a[4]); Sort(a[6], a[7]);
	Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]);
	Sort(a[0], a[3]); Sort(a[5], a[8]); Sort(a[4], a[7]);
	Sort(a[3], a[6]); Sort(a[1], a[4]); Sort(a[2], a[5]);
	Sort(a[4], a[7]); Sort(a[4], a[2]); Sort(a[6], a[4]);
	Sort(a[4], a[2]);

	outputImagekernel[row * imageWidth + col] = (uint8_t)a[4];   //Set the output image values.
}

__global__ void rgbMedianSharedFilter(unsigned char* inputImageKernel, unsigned char* outputImagekernel, int imageWidth, int imageHeight)
{
	//Set the row and col value for each thread.
	int threadX = threadIdx.x * 3;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	__shared__ unsigned char sharedmem[(TILE_SIZE + 2) * 3][(TILE_SIZE + 2)];  //initialize shared memory
	//Take some values.
	bool is_x_left = (threadIdx.x == 0), is_x_right = (threadIdx.x == TILE_SIZE - 1);
	bool is_y_top = (threadIdx.y == 0), is_y_bottom = (threadIdx.y == TILE_SIZE - 1);

	//Initialize with zero
	if (is_x_left) {
		sharedmem[threadIdx.x][threadIdx.y + 1] = 0;
		sharedmem[threadIdx.x + 1][threadIdx.y + 1] = 0;
		sharedmem[threadIdx.x + 2][threadIdx.y + 1] = 0;
	}
	else if (is_x_right) {
		sharedmem[threadX + 3][threadIdx.y + 1] = 0;
		sharedmem[threadX + 4][threadIdx.y + 1] = 0;
		sharedmem[threadX + 5][threadIdx.y + 1] = 0;
	}

	if (is_y_top) {
		sharedmem[threadX][threadIdx.y] = 0;
		sharedmem[threadX + 1][threadIdx.y] = 0;
		sharedmem[threadX + 2][threadIdx.y] = 0;
		if (is_x_left) {
			sharedmem[threadIdx.x][threadIdx.y] = 0;
			sharedmem[threadIdx.x + 1][threadIdx.y] = 0;
			sharedmem[threadIdx.x + 2][threadIdx.y] = 0;
		}
		else if (is_x_right) {
			sharedmem[threadX + 3][threadIdx.y] = 0;
			sharedmem[threadX + 4][threadIdx.y] = 0;
			sharedmem[threadX + 5][threadIdx.y] = 0;
		}
	}
	else if (is_y_bottom) {
		sharedmem[threadX][threadIdx.y + 2] = 0;
		sharedmem[threadX + 1][threadIdx.y + 2] = 0;
		sharedmem[threadX + 2][threadIdx.y + 2] = 0;
		if (is_x_right) {
			sharedmem[threadX + 3][threadIdx.y + 2] = 0;
			sharedmem[threadX + 4][threadIdx.y + 2] = 0;
			sharedmem[threadX + 5][threadIdx.y + 2] = 0;
		}
		else if (is_x_left) {
			sharedmem[threadIdx.x][threadIdx.y + 2] = 0;
			sharedmem[threadIdx.x + 1][threadIdx.y + 2] = 0;
			sharedmem[threadIdx.x + 2][threadIdx.y + 2] = 0;
		}
	}

	//Setup pixel values
	sharedmem[threadIdx.x + 1][threadIdx.y + 1] = inputImageKernel[row * imageWidth + col];
	//Check for boundry conditions.
	if (is_x_left && (col > 0))
		sharedmem[threadIdx.x][threadIdx.y + 1] = inputImageKernel[row * imageWidth + (col - 1)];
	else if (is_x_right && (col < imageWidth - 1))
		sharedmem[threadIdx.x + 2][threadIdx.y + 1] = inputImageKernel[row * imageWidth + (col + 1)];
	if (is_y_top && (row > 0)) {
		sharedmem[threadIdx.x + 1][threadIdx.y] = inputImageKernel[(row - 1) * imageWidth + col];
		if (is_x_left)
			sharedmem[threadIdx.x][threadIdx.y] = inputImageKernel[(row - 1) * imageWidth + (col - 1)];
		else if (is_x_right)
			sharedmem[threadIdx.x + 2][threadIdx.y] = inputImageKernel[(row - 1) * imageWidth + (col + 1)];
	}
	else if (is_y_bottom && (row < imageHeight - 1)) {
		sharedmem[threadIdx.x + 1][threadIdx.y + 2] = inputImageKernel[(row + 1) * imageWidth + col];
		if (is_x_right)
			sharedmem[threadIdx.x + 2][threadIdx.y + 2] = inputImageKernel[(row + 1) * imageWidth + (col + 1)];
		else if (is_x_left)
			sharedmem[threadIdx.x][threadIdx.y + 2] = inputImageKernel[(row + 1) * imageWidth + (col - 1)];
	}

	__syncthreads();   //Wait for all threads to be done.

	//Setup the filter.
	int a[9] = { sharedmem[threadIdx.x][threadIdx.y], sharedmem[threadIdx.x + 1][threadIdx.y], sharedmem[threadIdx.x + 2][threadIdx.y],
				  sharedmem[threadIdx.x][threadIdx.y + 1], sharedmem[threadIdx.x + 1][threadIdx.y + 1], sharedmem[threadIdx.x + 2][threadIdx.y + 1],
				  sharedmem[threadIdx.x][threadIdx.y + 2], sharedmem[threadIdx.x + 1][threadIdx.y + 2], sharedmem[threadIdx.x + 2][threadIdx.y + 2] };

	Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]);
	Sort(a[0], a[1]); Sort(a[3], a[4]); Sort(a[6], a[7]);
	Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]);
	Sort(a[0], a[3]); Sort(a[5], a[8]); Sort(a[4], a[7]);
	Sort(a[3], a[6]); Sort(a[1], a[4]); Sort(a[2], a[5]);
	Sort(a[4], a[7]); Sort(a[4], a[2]); Sort(a[6], a[4]);
	Sort(a[4], a[2]);

	outputImagekernel[row * imageWidth + col] = (uint8_t)a[4];   //Set the output image values.
}

__global__ void mFilter(const uint8_t* in, uint8_t* out, const size_t W, const size_t H)
{
	//int index = blockIdx.x * blockDim.x + threadIdx.x;
	int idx = threadIdx.x + blockIdx.x * blockDim.x + 1;
	int idy = threadIdx.y + blockIdx.y * blockDim.y + 1;
	int a[9] = {};
	if (idy < H - 1 && idx < W - 1)
	{
		for (int z2 = 0; z2 < 3; ++z2)
			for (int z1 = 0; z1 < 3; ++z1)
				a[3 * z2 + z1] = in[(idy - 1 + z2) * W + idx - 1 + z1];

		Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]);
		Sort(a[0], a[1]); Sort(a[3], a[4]); Sort(a[6], a[7]);
		Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]);
		Sort(a[0], a[3]); Sort(a[5], a[8]); Sort(a[4], a[7]);
		Sort(a[3], a[6]); Sort(a[1], a[4]); Sort(a[2], a[5]);
		Sort(a[4], a[7]); Sort(a[4], a[2]); Sort(a[6], a[4]);
		Sort(a[4], a[2]);

		out[idy * W + idx] = (uint8_t)a[4];
	}
}

__global__ void rgbMedianFilterGPU(const uint8_t* in, uint8_t* out, const size_t W, const size_t H) {
	//int index = blockIdx.x * blockDim.x + threadIdx.x;
	int idx = threadIdx.x * 3 + blockIdx.x * blockDim.x + 3;
	int idy = threadIdx.y + blockIdx.y * blockDim.y + 1;
	//int idy = 4;
	int r[9] = {};
	int g[9] = {};
	int b[9] = {};
	if (idy < H - 1 && idx < W - 3)
	{
		for (int z2 = 0; z2 < 3; ++z2)
			for (int z1 = 0; z1 < 3; ++z1) {
				r[z2 * 3 + z1] = in[(idy - 1 + z2) * W + idx - 3 + z1 * 3];
				g[z2 * 3 + z1] = in[(idy - 1 + z2) * W + idx - 3 + z1 * 3 + 1];
				b[z2 * 3 + z1] = in[(idy - 1 + z2) * W + idx - 3 + z1 * 3 + 2];
			}

		Sort(r[1], r[2]); Sort(r[4], r[5]); Sort(r[7], r[8]);
		Sort(r[0], r[1]); Sort(r[3], r[4]); Sort(r[6], r[7]);
		Sort(r[1], r[2]); Sort(r[4], r[5]); Sort(r[7], r[8]);
		Sort(r[0], r[3]); Sort(r[5], r[8]); Sort(r[4], r[7]);
		Sort(r[3], r[6]); Sort(r[1], r[4]); Sort(r[2], r[5]);
		Sort(r[4], r[7]); Sort(r[4], r[2]); Sort(r[6], r[4]);
		Sort(r[4], r[2]);

		Sort(g[1], g[2]); Sort(g[4], g[5]); Sort(g[7], g[8]);
		Sort(g[0], g[1]); Sort(g[3], g[4]); Sort(g[6], g[7]);
		Sort(g[1], g[2]); Sort(g[4], g[5]); Sort(g[7], g[8]);
		Sort(g[0], g[3]); Sort(g[5], g[8]); Sort(g[4], g[7]);
		Sort(g[3], g[6]); Sort(g[1], g[4]); Sort(g[2], g[5]);
		Sort(g[4], g[7]); Sort(g[4], g[2]); Sort(g[6], g[4]);
		Sort(g[4], g[2]);

		Sort(b[1], b[2]); Sort(b[4], b[5]); Sort(b[7], b[8]);
		Sort(b[0], b[1]); Sort(b[3], b[4]); Sort(b[6], b[7]);
		Sort(b[1], b[2]); Sort(b[4], b[5]); Sort(b[7], b[8]);
		Sort(b[0], b[3]); Sort(b[5], b[8]); Sort(b[4], b[7]);
		Sort(b[3], b[6]); Sort(b[1], b[4]); Sort(b[2], b[5]);
		Sort(b[4], b[7]); Sort(b[4], b[2]); Sort(b[6], b[4]);
		Sort(b[4], b[2]);

		out[idy * W + idx] = (uint8_t)r[4];
		out[idy * W + idx + 1] = (uint8_t)g[4];
		out[idy * W + idx + 2] = (uint8_t)b[4];
	}
}

bool MedianFilterGPU(uint8_t* image, uint8_t* outputImage, const size_t width, const size_t height, bool useSharedMemory) {
	//Cuda error and image values.
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start);

	int size = width * height * sizeof(char);

	//Initialize images.
	unsigned char* inputDeviceImage;
	CUDA_CALL(cudaMalloc((void**)&inputDeviceImage, size));
	CUDA_CALL(cudaMemcpy(inputDeviceImage, image, size, cudaMemcpyHostToDevice));
	
	uint8_t* deviceOutputImage;
	cudaMalloc((void**)&deviceOutputImage, size);
	//take block and grids.
	dim3 dimBlock(TILE_SIZE, TILE_SIZE);
	dim3 dimGrid((int)ceil((float)width / (float)TILE_SIZE), (int)ceil((float)height / (float)TILE_SIZE));

	//printf("\nDim grid %d %d %d\n", dimGrid.x, dimGrid.y, dimGrid.x * dimGrid.y);

	struct cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop, 0);
	size_t maxThreads = prop.maxGridSize[0];

	//Check for shared memories and call the kernel
	if (!useSharedMemory) {
		if (CHANNELS == 1) {
			mFilter << <dimGrid, dimBlock >> > (inputDeviceImage, deviceOutputImage, width, height);
		}
		else {
			rgbMedianFilterGPU << <dimGrid, dimBlock >> > (inputDeviceImage, deviceOutputImage, width, height);
		}
	} else {
		dimGrid = ((int)floorf((float)width / (float)TILE_SIZE), (int)floorf((float)height / (float)TILE_SIZE));
		if (CHANNELS == 1) {
			medianFilterSharedKernel << <dimGrid, dimBlock >> > (inputDeviceImage, deviceOutputImage, width, height);
		}
		else {
			rgbMedianSharedFilter << <dimGrid, dimBlock >> > (inputDeviceImage, deviceOutputImage, width, height);
		}
	}


	//CUDA_CALL(cudaMalloc((void**)&deviceOutputImage, size));
	//CUDA_CALL(cudaMalloc())

	// save output image to host.
	CUDA_CALL(cudaMemcpy(outputImage, deviceOutputImage, size, cudaMemcpyDeviceToHost));

	//Free the memory
	cudaFree(inputDeviceImage);
	cudaFree(deviceOutputImage);
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	float time = 0;
	cudaEventElapsedTime(&time, start, stop);
	printf("Time: %f ms\n", time);
	return true;
}

void Sort_CPU(int& a, int& b)
{
	const int d = a - b;
	const int m = ~(d >> 8);
	b += d & m;
	a -= d & m;
}

inline void Sort_CPU(int a[9]) //частично сортирует весь массив
{
	Sort_CPU(a[1], a[2]); Sort_CPU(a[4], a[5]); Sort_CPU(a[7], a[8]);
	Sort_CPU(a[0], a[1]); Sort_CPU(a[3], a[4]); Sort_CPU(a[6], a[7]);
	Sort_CPU(a[1], a[2]); Sort_CPU(a[4], a[5]); Sort_CPU(a[7], a[8]);
	Sort_CPU(a[0], a[3]); Sort_CPU(a[5], a[8]); Sort_CPU(a[4], a[7]);
	Sort_CPU(a[3], a[6]); Sort_CPU(a[1], a[4]); Sort_CPU(a[2], a[5]);
	Sort_CPU(a[4], a[7]); Sort_CPU(a[4], a[2]); Sort_CPU(a[6], a[4]);
	Sort_CPU(a[4], a[2]);
}

void MedianFilter(const uint8_t* src, uint8_t* dst, size_t width, size_t height)
{
	time_point t = ttime::now();
	int a[9];
	for (size_t y = 1; y < height - 1; y++)
	{
		for (size_t x = 1; x < width - 1; x++)
		{
			for (int z1 = 0; z1 < 3; z1++)
				for (int z2 = 0; z2 < 3; z2++)
					a[z1 * 3 + z2] = src[(y - 1 + z1) * width + x - 1 + z2];
			Sort_CPU(a);
			dst[y * width + x] = (uint8_t)a[4];
		}
	}
	printf("Time: %f ms\n", DURATION(t) / 1000.0);
}

void MedianFilterRGB(const uint8_t* src, uint8_t* dst, size_t width, size_t height)
{
	time_point t = ttime::now();
	int r[9], g[9], b[9]; 
	for (size_t y = 1; y < height - 1; y++)
	{
		for (size_t x = 3; x < width - 3; x += 3)
		{
			for (int z1 = 0; z1 < 3; z1++)
				for (int z2 = 0; z2 < 3; z2++) {
					r[z1 * 3 + z2] = src[(y - 1 + z1) * width + x - 3 + z2 * 3 + 0];
					g[z1 * 3 + z2] = src[(y - 1 + z1) * width + x - 3 + z2 * 3 + 1];
					b[z1 * 3 + z2] = src[(y - 1 + z1) * width + x - 3 + z2 * 3 + 2];
				}
			Sort_CPU(r);
			Sort_CPU(g);
			Sort_CPU(b);
			dst[y * width + x] = (uint8_t)r[4];
			dst[y * width + x + 1] = (uint8_t)g[4];
			dst[y * width + x + 2] = (uint8_t)b[4];
		}
	}
	printf("Duration %f\n", DURATION(t) / 1000.0);
}

bool cmp(const uint8_t* p1, const uint8_t* p2, size_t size) {
	for (int i = 0; i < size; i++)
		if (p1[i] != p2[i])
			return false;
	return true;
}

int main()
{
	int width, height, bpp;

	uint8_t* image = stbi_load("input/noised.jpg", &width, &height, &bpp, CHANNELS);
	uint8_t* gpu_image = (uint8_t*)malloc(width * height * CHANNELS);
	uint8_t* cpu_image = (uint8_t*)malloc(width * height * CHANNELS);

	stbi_write_jpg("input_image.jpg", width, height, CHANNELS, image, width);

	printf("Size of image:	pixels:	%d \n		width:	%d \n		height:	%d\n", width * height, width, height);

	printf("CPU\n");
	if (CHANNELS == 1) {
		MedianFilter(image, cpu_image, width * CHANNELS, height);
	}
	else {
		MedianFilterRGB(image, cpu_image, width * CHANNELS, height);
	}

	printf("Shared memory:\n");
	MedianFilterGPU(image, gpu_image, width * CHANNELS, height, true);

	printf("Global memory:\n");
	MedianFilterGPU(image, gpu_image, width * CHANNELS, height, false);

	if (cmp(cpu_image, gpu_image, width * height * CHANNELS)) {
		printf("CPU and GPU images are same!\n");
	} else {
		printf("CPU and GPU images are't same...\n");
	}
	stbi_write_jpg("output/result_image.jpg", width, height, CHANNELS, cpu_image, width);

	stbi_image_free(image);
	stbi_image_free(gpu_image);
	stbi_image_free(cpu_image);

	return 0;
}
