#include <stdio.h>
#include <omp.h>

const int N = 10000;

int f(int n) { return (n == N/2); }

int main()
{
    printf("GCC %d.%d / OpenMP %d\n", __GNUC__, __GNUC_MINOR__, _OPENMP);
    printf("omp_get_cancellation=%d\n", omp_get_cancellation());

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        int r = f(i);
        #pragma omp cancel for if (r)
    }
}
