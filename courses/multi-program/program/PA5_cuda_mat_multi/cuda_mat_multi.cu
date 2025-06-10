#include <stdio.h>
#include <time.h>

#include "utils.cuh"

#define ROWS 2500
#define COLS 1000

#if ROWS * COLS <= 2000
#define DATA_PRINT
#endif

FILE* fp;

__global__ void _kernel_matrixVectorMul(int* matrix, int* vector, int* result,
                                        int rows, int cols) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;

  if (idx < rows) {
    int sum = 0;
    for (int j = 0; j < cols; ++j)
      sum += matrix[idx * cols + j] * vector[j];
    result[idx] = sum;
  }
}

/// @brief 矩阵向量乘法并行实现
/// @return 执行时间（ms）
float matrixVectorMulParallel(int* h_matrix, int* h_vector, int* h_result,
                              int rows, int cols) {
  size_t matrix_size = rows * cols * sizeof(int);
  size_t vector_size = cols * sizeof(int);
  size_t result_size = rows * sizeof(int);

  int* d_matrix,
     * d_vector,
     * d_result;

  CUDA_CHECK(cudaMalloc(&d_matrix, matrix_size));
  CUDA_CHECK(cudaMalloc(&d_vector, vector_size));
  CUDA_CHECK(cudaMalloc(&d_result, result_size));

  CUDA_CHECK(cudaMemcpy(d_matrix, h_matrix, matrix_size, cudaMemcpyHostToDevice));
  CUDA_CHECK(cudaMemcpy(d_vector, h_vector, vector_size, cudaMemcpyHostToDevice));

  dim3 block(512);
  dim3 grid((rows - 1) / block.x + 1);

  float time = KERNEL_TIMER(_kernel_matrixVectorMul, false, grid, block,
                            d_matrix, d_vector, d_result, rows, cols);

  CUDA_CHECK(cudaMemcpy(h_result, d_result, result_size, cudaMemcpyDeviceToHost));

  CUDA_CHECK(cudaFree(d_matrix));
  CUDA_CHECK(cudaFree(d_vector));
  CUDA_CHECK(cudaFree(d_result));
  return time;
}

/// @brief 矩阵向量乘法串行实现
/// @return 执行时间（ms）
float matrixVectorMulSerial(int* matrix, int* vector, int* result,
                            int rows, int cols) {
  clock_t start, end;
  start = clock();
  for (int i = 0; i < rows; ++i) {
    int sum = 0;
    for (int j = 0; j < cols; ++j)
      sum += matrix[i * cols + j] * vector[j];
    result[i] = sum;
  }
  end = clock();
  return (float)(end - start) / CLOCKS_PER_SEC * 1000;
}

bool matchResult(int* a, int* b, int size) {
  for (int i = 0; i < size; ++i)
    if (a[i] != b[i])
      return false;
  return true;
}

int main() {
  srand(time(NULL));
  int* h_matrix = (int*)malloc(ROWS * COLS * sizeof(int));
  int* h_vector = (int*)malloc(COLS * sizeof(int));
  int* h_result = (int*)malloc(ROWS * sizeof(int));
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      h_matrix[i * COLS + j] = rand() % 11 - 5; // 随机化矩阵元素（-5 ~ 5）
      h_vector[j] = rand() % 11 - 5;            // 随机化向量元素（-5 ~ 5）
    }
  }

  fp = fopen("output.txt", "w");
  if (fp == NULL)
    perror("Failed to open file");
#ifdef DATA_PRINT
  dual_printf("Matrix:\n");
  print_matrix(h_matrix, ROWS, COLS);
  dual_printf("Vector:\n");
  print_vector(h_vector, COLS);
#endif

  float time_parallel = matrixVectorMulParallel(h_matrix, h_vector, h_result,
                                                ROWS, COLS);
#ifdef DATA_PRINT
  dual_printf("Parallel result:\n");
  print_vector(h_result, ROWS);
#endif

  int* result = (int*)malloc(ROWS * sizeof(int));
  float time_serial = matrixVectorMulSerial(h_matrix, h_vector, result,
                                            ROWS, COLS);
#ifdef DATA_PRINT
  dual_printf("Serial result:\n");
  print_vector(result, ROWS);
#endif

  if (matchResult(h_result, result, ROWS)) dual_printf("Result match!\n");
  else dual_printf("Result mismatch!\n");

  dual_printf("Parallel time: %f ms\n", time_parallel);
  dual_printf("Serial time: %f ms\n", time_serial);

  fclose(fp);
  free(h_matrix);
  free(h_vector);
  free(h_result);
  free(result);
  return 0;
}
