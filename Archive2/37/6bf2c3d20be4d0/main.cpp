#include <iostream>
#include <cmath>

double cosine_similarity(double *A, double *B, unsigned int Vector_Length)
{
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
     for(unsigned int i = 0u; i < Vector_Length; ++i) {
        dot += A[i] * B[i] ;
        denom_a += A[i] * A[i] ;
        denom_b += B[i] * B[i] ;
    }
    return dot / (std::sqrt(denom_a) * sqrt(denom_b)) ;
}

int main()
{
    double A[] = { 200.3, 99.5, 100.78 }, B[] = { 566.7, 199999.09, 1000.05 };
    std::cout << cosine_similarity(A, B, 3u);
}