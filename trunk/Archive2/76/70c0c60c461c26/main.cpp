
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <math.h>
#include "math_functions.h"

#include <csignal>
#include <stdio.h>
#include <thread>


cudaError_t CheckPrimes(unsigned* res_a, unsigned* res_b, unsigned long long bound_index);

__device__
bool is_prime(unsigned long long num){
    unsigned long long sq = (unsigned long long)sqrtf((double)num);
	unsigned long long res = 0ull;
	for (unsigned long long i = 3ull; i <= sq; i += 2ull){
		res = num / i;
		if (res * i == num) return false;
	}
	return true;
}

__global__
void is_prime_kernel(unsigned num, bool* is){
	auto sq = (unsigned)(rsqrtf((float)num));
	auto res = 0u;
	for (auto i = 3u; i <= sq; i += 2u){
		res = num / i;
		if (res * i == num){
			*is = false;
			return;
		}
	}
	*is = true;
	return;
}

__global__
void prime_checker_kernel(
	unsigned* count_arr_a, unsigned* count_arr_b,
	unsigned long long* bound_index,
	volatile unsigned* is_done
	){

	unsigned id = threadIdx.x + blockIdx.x * blockDim.x;

	unsigned long long a = *bound_index + id * 1024u + 1u;
	unsigned long long b = a + 1u;

	count_arr_a[id] = 0u;
	count_arr_b[id] = 0u;

	/*
	for (unsigned long long i = 0u; i < 1024u; ++i){
		unsigned long long c = a + b;
		++a;
		++b;
		if (is_prime(c)){
			unsigned char is_even = i & 1u;
			count_arr_a[id] += is_even;
			count_arr_b[id] += is_even;
		}
	}
	*/

	*is_done = true;
	__threadfence_system();

	return;
}

void signal_handler(int signal){
	cudaDeviceReset();
	if (cudaDeviceReset() != cudaSuccess){
		fprintf(stderr, "cudaDeviceReset failed!");
	}
	printf("ending\n");
	exit(0);
}

int main(){
	const unsigned k_NumChunks = 1024u;
	unsigned res_a[k_NumChunks];
	unsigned res_b[k_NumChunks];

	std::signal(SIGINT, signal_handler);

	// do the thing
    cudaError_t cudaStatus = CheckPrimes(res_a, res_b, UINT32_MAX);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cuda - main failed!\n%u - %s\n", cudaStatus, cudaGetErrorString(cudaStatus));
        return 1;
    }

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }

	auto num_a = 0ull;
	auto num_b = 0ull;
	for (auto i = 0u; i < k_NumChunks; ++i){
		num_a += res_a[i];
		num_b += res_b[i];
	}
	
	printf("results:\n");
	printf("%ull\n", num_a);
	printf("%ull\n", num_b);

    return 0;
}

cudaError_t CheckPrimes(unsigned* res_a, unsigned* res_b, unsigned long long bound_index){
    cudaError_t cudaStatus;
	
	const unsigned k_NumChunks = 1024u;
	unsigned* dev_res_a;
    unsigned* dev_res_b;
	unsigned long long* dev_index;

	// mapped crap
	volatile unsigned* host_map_is_done;
	volatile unsigned* dev_map_is_done;

    // Choose which GPU to run on
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }
	
	cudaSetDeviceFlags(cudaDeviceMapHost);

	// --- allocate stuff on gpu ---
    cudaStatus = cudaMalloc((void**)&dev_res_a, k_NumChunks * sizeof(unsigned));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!\n");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_res_b, k_NumChunks * sizeof(unsigned));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!\n");
        goto Error;
    }

	cudaStatus = cudaMalloc((void**)&dev_index, sizeof(unsigned long long));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!\n");
		goto Error;
	}

	// --- mapped memory ---
	cudaStatus = cudaHostAlloc((void**)&host_map_is_done, sizeof(unsigned), cudaHostAllocMapped);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaHostAlloc failed!\n");
		goto Error;
	}

	cudaStatus = cudaHostGetDevicePointer((unsigned**)&dev_map_is_done, (void*)host_map_is_done, 0);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaHostGetDevicePointer failed!\n");
		goto Error;
	}

	*host_map_is_done = 0u;

	// --- copy stuff to gpu ---
	cudaStatus = cudaMemcpy(dev_index, &bound_index, sizeof(unsigned long long), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!\n");
		goto Error;
	}

	printf("starting kernel!\n");

	// Start Kernel
    prime_checker_kernel<<<1, 1>>>(dev_res_a, dev_res_b, dev_index, dev_map_is_done);
	
    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "prime_checker_kernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }

	while (!*host_map_is_done){
		printf("waiting 100ms\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	printf("done!\n");

	// cudaDeviceSynchronize waits for the kernel to finish, and returns
	// any errors encountered during the launch.
	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching prime_checker_kernel!\n", cudaStatus);
		fprintf(stderr, "msg: %s\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}

	printf("synced!\n");

	// copy stuff to host
    cudaStatus = cudaMemcpy(res_a, dev_res_a, k_NumChunks * sizeof(unsigned), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	cudaStatus = cudaMemcpy(res_b, dev_res_b, k_NumChunks * sizeof(unsigned), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		goto Error;
	}

Error:
    cudaFree(dev_res_a);
	cudaFree(dev_res_b);
	
    return cudaStatus;
}
