#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

static long num_steps = 100000000;
double step, pi;
int num_threads = 4;
CRITICAL_SECTION cs;

typedef struct {
  int thread_id;
  int start;
  int end;
  double partial_sum;
} ThreadData;

DWORD WINAPI compute_pi_thread(LPVOID param) {
  ThreadData* data = (ThreadData*)param;
  double x, local_sum = 0.0;

  for (int i = data->start; i < data->end; ++i) {
    x = (i + 0.5) * step;
    local_sum += 4.0 / (1.0 + x * x);
  }

  data->partial_sum = local_sum;

  EnterCriticalSection(&cs);
  pi += local_sum * step;
  LeaveCriticalSection(&cs);

  return 0;
}

void parallel_pi_calculation() {
  HANDLE* threads = (HANDLE*)malloc(num_threads * sizeof(HANDLE));
  ThreadData* thread_data = (ThreadData*)malloc(num_threads * sizeof(ThreadData));
  
  InitializeCriticalSection(&cs);
  
  int chunk_size = num_steps / num_threads;
  
  for (int i = 0; i < num_threads; i++) {
    thread_data[i].thread_id = i;
    thread_data[i].start = i * chunk_size;
    thread_data[i].end = (i == num_threads - 1) ? num_steps : (i + 1) * chunk_size;
    thread_data[i].partial_sum = 0.0;
    
    threads[i] = CreateThread(NULL, 0, compute_pi_thread, &thread_data[i], 0, NULL);
  }
  
  WaitForMultipleObjects(num_threads, threads, TRUE, INFINITE);
  
  for (int i = 0; i < num_threads; i++) {
      CloseHandle(threads[i]);
  }
  
  DeleteCriticalSection(&cs);
  free(threads);
  free(thread_data);
}

double serial_pi_calculation() {
  double x, sum = 0.0;
  for (int i = 0; i < num_steps; i++) {
    x = (i + 0.5) * step;
    sum += 4.0 / (1.0 + x * x);
  }
  return step * sum;
}

void main() {
  ARGE_INTEGER freq, start, end;
  double serial_time, parallel_time;
  
  QueryPerformanceFrequency(&freq);
  step = 1.0 / (double)num_steps;
  
  printf("Computing PI with %ld steps using WinAPI threads\n", num_steps);
  printf("Number of threads: %d\n\n", num_threads);
  
  QueryPerformanceCounter(&start);
  double serial_pi = serial_pi_calculation();
  QueryPerformanceCounter(&end);
  serial_time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
  
  pi = 0.0;
  QueryPerformanceCounter(&start);
  parallel_pi_calculation();
  QueryPerformanceCounter(&end);
  parallel_time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
  
  printf("Serial PI = %.10f, Time = %.6f seconds\n", serial_pi, serial_time);
  printf("Parallel PI = %.10f, Time = %.6f seconds\n", pi, parallel_time);
  printf("Speedup = %.2f\n", serial_time / parallel_time);
  printf("Accuracy: |serial - parallel| = %.2e\n", fabs(serial_pi - pi));
  
  return 0;
}