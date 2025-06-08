#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: %s <total_points>\n", argv[0]);
    return 1;
  }
  int total_points = atoi(argv[1]);

  int points_in_circle;
  double x, y, pi_estimate,
         start_time, end_time, serial_time;
  const int kThreadsNum[7] = {1, 2, 4, 6, 10, 12, 16};

  for (int threads_num_idx = 0; threads_num_idx < 7; ++threads_num_idx) {
    points_in_circle = 0;
    start_time = omp_get_wtime();
    printf("Estimating Pi using %d points with %d threads...\n", total_points, kThreadsNum[threads_num_idx]);

    #pragma omp parallel for reduction(+:points_in_circle) private(x, y) num_threads(kThreadsNum[threads_num_idx])
    for (int i = 0; i < total_points; ++i) {
      unsigned int seed = time(NULL) + omp_get_thread_num() + i;
      x = (double)rand_r(&seed) / RAND_MAX;
      y = (double)rand_r(&seed) / RAND_MAX;
      if (x * x + y * y <= 1.0)
        ++points_in_circle;
    }
    pi_estimate = 4.0 * points_in_circle / total_points;
  
    printf("Estimated value of Pi: %.7f\n", pi_estimate);
    end_time = omp_get_wtime();

    if (threads_num_idx == 0)
      serial_time = end_time - start_time;

    printf("Time taken: %.6f seconds\n", end_time - start_time);
    printf("Speedup: %.2f\n", serial_time / (end_time - start_time));
  }
  return 0;
}