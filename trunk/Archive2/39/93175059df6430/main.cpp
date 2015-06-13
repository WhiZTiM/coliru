#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char **argv) {
  int test_size, i;
  double *vector, mean, stddeviation, start_time, duration;

  if (argc != 2) {
    printf("Usage: %s <test_size>\n", argv[0]);
    return 1;
  }

  srand((int) omp_get_wtime());

  test_size = atoi(argv[1]);
  printf("Test Size: %d\n", test_size);

  vector = (double *) malloc(test_size * sizeof(double));
  for (i = 0; i < test_size; i++) {
    vector[i] = rand();
  }

  start_time = omp_get_wtime();
  mean = 0;
  stddeviation = 0;
#pragma omp parallel default(shared) private(i)
  {
#pragma omp for reduction(+:mean)
    for (i = 0; i < test_size; i++) {
      mean += vector[i];
    }
#pragma omp single
    mean /= test_size;

#pragma omp for reduction(+:stddeviation)
    for (i = 0; i < test_size; i++) {
      stddeviation += (vector[i] - mean)*(vector[i] - mean);
    }
  }
  stddeviation = sqrt(stddeviation / test_size);
  duration = omp_get_wtime() - start_time;

  printf("Std. Deviation = %lf\n", stddeviation);
  printf("Duration: %fms\n", duration*1000);

  return 0;
}