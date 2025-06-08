#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int total_rows = 3, cols = 2;
  int rows_per_proc = total_rows / size;
  int remainder = total_rows % size;
  int local_rows = rows_per_proc + (rank < remainder ? 1 : 0);

  // 在主进程中定义完整矩阵
  int** global_matrix = NULL;
  if (rank == 0) {
    global_matrix = (int**)malloc(total_rows * sizeof(int*));
    for (int i = 0; i < total_rows; i++) {
      global_matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    // 初始化矩阵数据
    int init_data[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    for (int i = 0; i < total_rows; i++) {
      for (int j = 0; j < cols; j++) {
        global_matrix[i][j] = init_data[i][j];
      }
    }
    
    printf("Original Matrix:\n");
    for (int i = 0; i < total_rows; i++) {
      for (int j = 0; j < cols; j++) {
        printf("%d ", global_matrix[i][j]);
      }
      printf("\n");
    }
    printf("\nVector: [7, 8]\n\n");
  }

  // 广播向量数据到所有进程
  int vector[2] = {7, 8};
  MPI_Bcast(vector, cols, MPI_INT, 0, MPI_COMM_WORLD);

  // 计算各进程分配的行数和偏移量
  int* sendcounts = (int*)malloc(size * sizeof(int));
  int* displs = (int*)malloc(size * sizeof(int));
  int offset = 0;
  for (int i = 0; i < size; i++) {
    sendcounts[i] = (rows_per_proc + (i < remainder ? 1 : 0)) * cols;
    displs[i] = offset;
    offset += sendcounts[i];
  }

  // 分配本地矩阵内存
  int* local_matrix = (int*)malloc(local_rows * cols * sizeof(int));

  // 将矩阵数据转换为一维数组用于散发
  int* matrix_data = NULL;
  if (rank == 0) {
    matrix_data = (int*)malloc(total_rows * cols * sizeof(int));
    for (int i = 0; i < total_rows; i++) {
      for (int j = 0; j < cols; j++) {
        matrix_data[i * cols + j] = global_matrix[i][j];
      }
    }
  }

  // 分发矩阵数据
  MPI_Scatterv(matrix_data, sendcounts, displs, MPI_INT,
         local_matrix, local_rows * cols, MPI_INT, 0, MPI_COMM_WORLD);

  // 并行计算本地结果
  int* local_result = (int*)malloc(local_rows * sizeof(int));
  for (int i = 0; i < local_rows; i++) {
    local_result[i] = 0;
    for (int j = 0; j < cols; j++) {
      local_result[i] += local_matrix[i * cols + j] * vector[j];
    }
  }

  printf("Process %d computed %d rows\n", rank, local_rows);

  // 计算结果收集的参数
  int* result_counts = (int*)malloc(size * sizeof(int));
  int* result_displs = (int*)malloc(size * sizeof(int));
  offset = 0;
  for (int i = 0; i < size; i++) {
    result_counts[i] = rows_per_proc + (i < remainder ? 1 : 0);
    result_displs[i] = offset;
    offset += result_counts[i];
  }

  int* final_result = NULL;
  if (rank == 0) {
    final_result = (int*)malloc(total_rows * sizeof(int));
  }

  // 收集所有计算结果
  MPI_Gatherv(local_result, local_rows, MPI_INT,
        final_result, result_counts, result_displs, MPI_INT, 0, MPI_COMM_WORLD);

  // 主进程输出结果到文件和控制台
  if (rank == 0) {
    FILE* output_file = fopen("result.txt", "w");
    if (output_file != NULL) {
      fprintf(output_file, "Matrix-Vector Multiplication Result:\n");
      fprintf(output_file, "Matrix:\n");
      fprintf(output_file, "1 2\n3 4\n5 6\n");
      fprintf(output_file, "Vector: [7, 8]\n");
      fprintf(output_file, "Result:\n");
      for (int i = 0; i < total_rows; i++) {
        fprintf(output_file, "%d\n", final_result[i]);
      }
      fclose(output_file);
      printf("Results written to result.txt\n");
    } else {
      printf("Error: Could not open result.txt for writing\n");
    }
    
    // 同时在控制台输出
    printf("\nFinal Result vector:\n");
    for (int i = 0; i < total_rows; i++) {
      printf("%d\n", final_result[i]);
    }
  }

  // 释放内存
  free(local_matrix);
  free(local_result);
  free(sendcounts);
  free(displs);
  free(result_counts);
  free(result_displs);

  if (rank == 0) {
    if (global_matrix != NULL) {
      for (int i = 0; i < total_rows; i++) {
        free(global_matrix[i]);
      }
      free(global_matrix);
    }
    if (matrix_data != NULL) {
      free(matrix_data);
    }
    if (final_result != NULL) {
      free(final_result);
    }
  }

  MPI_Finalize();
  return 0;
}
