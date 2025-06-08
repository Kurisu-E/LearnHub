#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <cuda_runtime.h>

#define CUDA_CHECK(call) \
do { \
  cudaError_t error = call; \
  if (error != cudaSuccess) { \
    fprintf(stderr, "CUDA error at %s:%d - %s\n", __FILE__, __LINE__, \
        cudaGetErrorString(error)); \
    exit(EXIT_FAILURE); \
  } \
} while(0)

__global__ void matrix_vector_mult_kernel(int* matrix, int* vector, int* result, int rows, int cols) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  
  if (idx < rows) {
    int sum = 0;
    for (int j = 0; j < cols; j++) {
      sum += matrix[idx * cols + j] * vector[j];
    }
    result[idx] = sum;
  }
}

void matrix_vector_cuda(int* h_matrix, int* h_vector, int* h_result, int rows, int cols) {
  size_t matrix_size = rows * cols * sizeof(int);
  size_t vector_size = cols * sizeof(int);
  size_t result_size = rows * sizeof(int);
  
  int *d_matrix, *d_vector, *d_result;
  CUDA_CHECK(cudaMalloc(&d_matrix, matrix_size));
  CUDA_CHECK(cudaMalloc(&d_vector, vector_size));
  CUDA_CHECK(cudaMalloc(&d_result, result_size));
  
  CUDA_CHECK(cudaMemcpy(d_matrix, h_matrix, matrix_size, cudaMemcpyHostToDevice));
  CUDA_CHECK(cudaMemcpy(d_vector, h_vector, vector_size, cudaMemcpyHostToDevice));
  
  int threadsPerBlock = 256;
  int blocksPerGrid = (rows + threadsPerBlock - 1) / threadsPerBlock;
  
  matrix_vector_mult_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_matrix, d_vector, d_result, rows, cols);
  CUDA_CHECK(cudaGetLastError());
  
  CUDA_CHECK(cudaMemcpy(h_result, d_result, result_size, cudaMemcpyDeviceToHost));
  
  CUDA_CHECK(cudaFree(d_matrix));
  CUDA_CHECK(cudaFree(d_vector));
  CUDA_CHECK(cudaFree(d_result));
}

int main() {
  int matrix_data[6] = {1, 2, 3, 4, 5, 6};
  int vector[2] = {7, 8};
  int rows = 3, cols = 2;
  
  int* result_cpu = (int*)malloc(rows * sizeof(int));
  int* result_gpu = (int*)malloc(rows * sizeof(int));
  
  if (result_cpu == NULL || result_gpu == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return EXIT_FAILURE;
  }
  
  // CPU计算
  clock_t start_cpu = clock();
  for (int i = 0; i < rows; i++) {
    result_cpu[i] = 0;
    for (int j = 0; j < cols; j++) {
      result_cpu[i] += matrix_data[i * cols + j] * vector[j];
    }
  }
  clock_t end_cpu = clock();
  double cpu_time = ((double)(end_cpu - start_cpu)) / CLOCKS_PER_SEC;
  
  // GPU计算
  cudaEvent_t start_gpu, stop_gpu;
  CUDA_CHECK(cudaEventCreate(&start_gpu));
  CUDA_CHECK(cudaEventCreate(&stop_gpu));
  
  CUDA_CHECK(cudaEventRecord(start_gpu, 0));
  matrix_vector_cuda(matrix_data, vector, result_gpu, rows, cols);
  CUDA_CHECK(cudaEventRecord(stop_gpu, 0));
  CUDA_CHECK(cudaEventSynchronize(stop_gpu));
  
  float gpu_time;
  CUDA_CHECK(cudaEventElapsedTime(&gpu_time, start_gpu, stop_gpu));
  
  printf("Matrix (3x2):\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", matrix_data[i * cols + j]);
    }
    printf("\n");
  }
  printf("\nVector: [%d, %d]\n\n", vector[0], vector[1]);
  
  printf("CPU Result:\n");
  for (int i = 0; i < rows; i++) {
    printf("%d\n", result_cpu[i]);
  }
  
  printf("\nGPU Result:\n");
  for (int i = 0; i < rows; i++) {
    printf("%d\n", result_gpu[i]);
  }
  
  bool correct = true;
  for (int i = 0; i < rows; i++) {
    if (result_cpu[i] != result_gpu[i]) {
      correct = false;
      break;
    }
  }
  
  printf("\nVerification: %s\n", correct ? "PASSED" : "FAILED");
  printf("CPU Time: %.6f seconds\n", cpu_time);
  printf("GPU Time: %.6f milliseconds\n", gpu_time);
  
  FILE* output_file = fopen("cuda_result.txt", "w");
  if (output_file != NULL) {
    fprintf(output_file, "CUDA Matrix-Vector Multiplication Result:\n");
    fprintf(output_file, "Matrix:\n1 2\n3 4\n5 6\n");
    fprintf(output_file, "Vector: [7, 8]\n");
    fprintf(output_file, "Result:\n");
    for (int i = 0; i < rows; i++) {
      fprintf(output_file, "%d\n", result_gpu[i]);
    }
    fprintf(output_file, "\nPerformance:\n");
    fprintf(output_file, "CPU Time: %.6f seconds\n", cpu_time);
    fprintf(output_file, "GPU Time: %.6f milliseconds\n", gpu_time);
    fclose(output_file);
    printf("Results written to cuda_result.txt\n");
  }
  
  free(result_cpu);
  free(result_gpu);
  CUDA_CHECK(cudaEventDestroy(start_gpu));
  CUDA_CHECK(cudaEventDestroy(stop_gpu));
  
  return 0;
}
