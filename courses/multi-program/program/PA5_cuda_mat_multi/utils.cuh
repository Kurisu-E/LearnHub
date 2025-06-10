#ifndef UTILS_CUH_
#define UTILS_CUH_

#include <stdio.h>
#include <stdarg.h>

extern FILE* fp;

/// @brief 检查 CUDA 函数运行时错误
/// @param error CUDA 运行时函数
#define CUDA_CHECK(error) _cudaCheck(error, __FILE__, __LINE__)

/// @brief 检查 CUDA kernel 函数运行时错误
#define KERNEL_CHECK() _kernelCheck(__FILE__, __LINE__)

/// @brief CUDA kernel 函数计时器
/// @param kernel_name kernel 函数名
/// @param print 是否打印计时结果，true 打印，false 不打印
#define KERNEL_TIMER(kernel_name, print, grid, block, ...) \
  _kernelTimer((void*)kernel_name, #kernel_name, print, grid, block, \
               ##__VA_ARGS__)

cudaError_t _cudaCheck(cudaError_t error, const char* file, int line) {
  if (error != cudaSuccess) {
    printf("CUDA error:\nerror_code = %d\nfile = %s\nline = %d\n\
           errName = %s\nerrString = %s\n",
           error, file, line,
           cudaGetErrorName(error), cudaGetErrorString(error));
    return error;
  }
  return error;
}

void _kernelCheck(const char* file, int line) {
  cudaError_t error = cudaGetLastError();
  if (error != cudaSuccess)
    printf("CUDA error:\nerror_code = %d\nfile = %s\nline = %d\n\
           errName = %s\nerrString = %s\n",
           error, file, line,
           cudaGetErrorName(error), cudaGetErrorString(error));
}

template<typename... Args>
float _kernelTimer(void* kernel_ptr, const char* kernel_name, const bool print,
                   dim3 grid, dim3 block, Args... args) {
  cudaEvent_t start, stop;
  CUDA_CHECK(cudaEventCreate(&start));
  CUDA_CHECK(cudaEventCreate(&stop));

  CUDA_CHECK(cudaEventRecord(start));
  ((void(*)(Args...))kernel_ptr)<<<grid, block>>>(args...);
  KERNEL_CHECK();
  CUDA_CHECK(cudaEventRecord(stop));

  CUDA_CHECK(cudaEventSynchronize(stop));
  float milliseconds = 0;
  CUDA_CHECK(cudaEventElapsedTime(&milliseconds, start, stop));
  CUDA_CHECK(cudaEventDestroy(start));
  CUDA_CHECK(cudaEventDestroy(stop));

  if (print == true)
    printf("Kernel %s execution time: %.6f ms\n", kernel_name, milliseconds);
  return milliseconds;
}

/// @brief 将格式化字符串输出到标准输出和文件，
/// 如果文件指针 `fp` 为 `NULL`，则只输出到标准输出
void dual_printf(const char *format, ...) {
  va_list args1, args2;
  va_start(args1, format);
  va_copy(args2, args1);

  vprintf(format, args1);
  if (fp != NULL) {
    vfprintf(fp, format, args2);
    fflush(fp);
  }

  va_end(args1);
  va_end(args2);
}

void print_vector(int* vector, int len) {
  dual_printf(" [");
  for (int i = 0; i < len; i++) {
    dual_printf("%5d", vector[i]);
  }
  dual_printf(" ]\n");
}

void print_matrix(int* matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    dual_printf(" |");
    for (int j = 0; j < cols; j++) {
      dual_printf("%3d", matrix[i * cols + j]);
    }
    dual_printf(" |\n");
  }
}

#endif // UTILS_CUH_