#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <mpi.h>

#define ROWS 25
#define COLS 10

FILE* fp = NULL;

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

void matrix_vector_multiplication(int* matrix, int* vector, int* result, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    result[i] = 0;
    for (int j = 0; j < cols; ++j) {
      result[i] += matrix[i * cols + j] * vector[j];
    }
  }
}

int main(int argc, char* argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  int local_rows = ROWS / size + (int)(rank < ROWS % size);

  // 主进程内定义矩阵和向量，通过随机值初始化
  // 矩阵展平便于发放和接收
  int* matrix = NULL,
     * vector = (int*)malloc(COLS * sizeof(int)),
     * result = NULL;
  if (rank == 0) {
    srand(time(NULL));
    matrix = (int*)malloc(ROWS * COLS * sizeof(int));
    result = (int*)malloc(ROWS * sizeof(int));
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        matrix[i * COLS + j] = rand() % 11 - 5; // 随机化矩阵元素（-5 ~ 5）
        vector[j] = rand() % 11 - 5;            // 随机化向量元素（-5 ~ 5）
      }
    }

    fp = fopen("output.txt", "w");
    if (fp == NULL)
      perror("Failed to open file");
    dual_printf("Matrix:\n");
    print_matrix(matrix, ROWS, COLS);
    dual_printf("Vector:\n");
    print_vector(vector, COLS);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  
  // 分发矩阵和向量到各个进程
  int* sendcounts = (int*)malloc(size * sizeof(int)),
     * displs = (int*)malloc(size * sizeof(int)),
     * local_matrix = (int*)malloc(local_rows * COLS * sizeof(int)),
       offset = 0;
  for (int i = 0; i < size; ++i) {
    sendcounts[i] = (ROWS / size + (int)(i < ROWS % size)) * COLS;
    displs[i] = offset;
    offset += sendcounts[i];
  }
  MPI_Scatterv(matrix, sendcounts, displs, MPI_INT,
               local_matrix, local_rows * COLS, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(vector, COLS, MPI_INT, 0, MPI_COMM_WORLD);

  // 每个进程计算其对应的行向量与向量的乘积
  int* local_result = (int*)malloc(local_rows * sizeof(int));
  matrix_vector_multiplication(local_matrix, vector, local_result, local_rows, COLS);
  MPI_Barrier(MPI_COMM_WORLD);

  // 收集每个进程的结果
  offset = 0;
  for (int i = 0; i < size; ++i) {
    sendcounts[i] = ROWS / size + (int)(i < ROWS % size);
    displs[i] = offset;
    offset += sendcounts[i];
  }
  MPI_Gatherv(local_result, local_rows, MPI_INT,
              result, sendcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

  // 打印结果
  if (rank == 0) {
    for (int i = 0; i < size; ++i)
      dual_printf("Process %d has %d rows.\n", i, sendcounts[i]);
    dual_printf("Result vector:\n");
    print_vector(result, ROWS);

    dual_printf("Serial result vector:\n");
    matrix_vector_multiplication(matrix, vector, result, ROWS, COLS);
    print_vector(result, ROWS);
  }

  // 释放内存
  free(vector);
  free(local_matrix);
  free(local_result);
  free(sendcounts);
  free(displs);
  if (rank == 0) {
    free(matrix);
    free(result);
  }
  MPI_Finalize();
  return 0;
}
