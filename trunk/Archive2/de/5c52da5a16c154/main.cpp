const int N = 10000;

int main()
{
  #pragma omp parallel for
  for (int i = 0; i < N; i++) {
    #pragma omp cancel for
  }
}
