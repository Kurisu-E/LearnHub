void matrixMultiply(int** A, int** B, int** C, int n, int m, int p) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < m; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

int** A, ** B, ** C_serial, ** C_parallel;
int N, M, P, num_threads;

typedef struct {
  int start_row;
  int end_row;
} ThreadArgs;

void matrixMultiply(int** A, int** B, int** C, int n, int m, int p) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < m; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void* threadMultiply(void* arg) {
  ThreadArgs* args = (ThreadArgs* )arg;
  for (int i = args->start_row; i < args->end_row; i++) {
    for (int j = 0; j < P; j++) {
      C_parallel[i][j] = 0;
      for (int k = 0; k < M; k++) {
        C_parallel[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  pthread_exit(NULL);
}

void initMatrix(int*** matrix, int rows, int cols) {
  *matrix = (int** )malloc(rows * sizeof(int*));
  for (int i = 0; i < rows; i++) {
    (*matrix)[i] = (int*)malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
      (*matrix)[i][j] = rand() % 10;
    }
  }
}

int verifyResult(int** C1, int** C2, int n, int p) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      if (C1[i][j] != C2[i][j]) return 0;
    }
  }
  return 1;
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    printf("Usage: %s N M P num_threads\n", argv[0]);
    return 1;
  }

  N = atoi(argv[1]);
  M = atoi(argv[2]);
  P = atoi(argv[3]);
  num_threads = atoi(argv[4]);

  // 初始化矩阵
  srand(time(NULL));
  initMatrix(&A, N, M);
  initMatrix(&B, M, P);
  C_serial = (int** )malloc(N * sizeof(int*));
  C_parallel = (int** )malloc(N * sizeof(int*));
  for (int i = 0; i < N; i++) {
    C_serial[i] = (int*)malloc(P * sizeof(int));
    C_parallel[i] = (int*)malloc(P * sizeof(int));
  }

  // 串行计算并计时
  struct timeval start, end;
  gettimeofday(&start, NULL);
  matrixMultiply(A, B, C_serial, N, M, P);
  gettimeofday(&end, NULL);
  double serial_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

  // 并行计算并计时
  gettimeofday(&start, NULL);
  pthread_t threads[num_threads];
  ThreadArgs args[num_threads];
  int rows_per_thread = N / num_threads;
  for (int i = 0; i < num_threads; i++) {
    args[i].start_row = i * rows_per_thread;
    args[i].end_row = (i == num_threads-1) ? N : (i+1)*rows_per_thread;
    pthread_create(&threads[i], NULL, threadMultiply, &args[i]);
  }
  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }
  gettimeofday(&end, NULL);
  double parallel_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

  // 验证结果
  if (verifyResult(C_serial, C_parallel, N, P)) {
    printf("Results match!\n");
    printf("Serial Time: %.6f s\n", serial_time);
    printf("Parallel Time: %.6f s\n", parallel_time);
    printf("Speedup: %.2f\n", serial_time / parallel_time);
  } else {
    printf("Results mismatch!\n");
  }

  return 0;
}