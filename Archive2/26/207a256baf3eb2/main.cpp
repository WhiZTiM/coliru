#include <math.h>
#include <stdio.h>
#include <emmintrin.h>
#include <xmmintrin.h>

__m128 my_exp2(__m128 x){
    /* x = u + n where u in [0, 1] */
    __m128i n = _mm_cvttps_epi32(x);
    __m128 d, u = _mm_sub_ps(x, _mm_cvtepi32_ps(n));

    /* taylor series for 2^u */
    d = _mm_set1_ps(0.013670309453328856f);
    d *= u;
    d += _mm_set1_ps(0.05174499776416041f);
    d *= u;
    d += _mm_set1_ps(0.24160435727005664f);
    d *= u;
    d += _mm_set1_ps(0.6929729221730601f);
    d *= u;
    d += _mm_set1_ps(1.000003492907698f);

    /* use floating point representation to calculate 2^n */
    /* _mm_shl_epi32 only available with XOP instruction set */
    n = _mm_add_epi32(n, _mm_set1_epi32(127));
    n = _mm_slli_epi32(n, 23);

    /* 2^x = 2^(u + n) = 2^u * 2^n */
    return _mm_mul_ps(d, *(__m128*)&n);
}

__m128 my_exp(__m128 x){
    /* e^x = 2^(x/log(2)) */
    return my_exp2(_mm_mul_ps(x, _mm_set1_ps(1.4426950408889634f)));
}

int main(){
    __m128 a;
    float *f = (float*)&a;
    f[0] = 0.1f;
    f[1] = 1.0f;
    f[2] = 6.66f;
    f[3] = 13.37f;

    printf("expected: %f %f %f %f\n", expf(f[0]), expf(f[1]), expf(f[2]), expf(f[3]));

    a = my_exp(a);

    printf("result  : %f %f %f %f\n", f[0], f[1], f[2], f[3]);
    return 0;
}
