#include <math.h>
#include <stdio.h>
#include <emmintrin.h>
#include <xmmintrin.h>

__m128 my_exp2i(__m128i i){
    /* use floating point representation to calculate 2^n */
    i = _mm_add_epi32(i, _mm_set1_epi32(127));
    i = _mm_slli_epi32(i, 23);
    return *(__m128*)&i;
}

__m128 my_exp2(__m128 x){
    __m128i i;
    __m128 d, u;

    /* clamp instead of overflow */
    x = _mm_min_ps(x, _mm_set1_ps(+128.0f));
    x = _mm_max_ps(x, _mm_set1_ps(-128.0f));

    /* x = u + i where u in [-1, 1] */
    i = _mm_cvttps_epi32(x);
    u = _mm_sub_ps(x, _mm_cvtepi32_ps(i));

    /* chebyshev approximation for 2^u with u in [-1, +1] */
    d = _mm_set1_ps(0.001356407436915082f);
    d = _mm_mul_ps(d, u);
    d = _mm_add_ps(d, _mm_set1_ps(0.009851424345691898f));
    d = _mm_mul_ps(d, u);
    d = _mm_add_ps(d, _mm_set1_ps(0.05549544590272578f));
    d = _mm_mul_ps(d, u);
    d = _mm_add_ps(d, _mm_set1_ps(0.24013878195285074f));
    d = _mm_mul_ps(d, u);
    d = _mm_add_ps(d, _mm_set1_ps(0.6931476620023692f));
    d = _mm_mul_ps(d, u);
    d = _mm_add_ps(d, _mm_set1_ps(1.0000048759242612f));

    /* 2^x = 2^(u + i) = 2^u * 2^i */
    return _mm_mul_ps(d, my_exp2i(i));
}

__m128 my_exp(__m128 x){
    /* e^x = 2^(x/log(2)) */
    return my_exp2(_mm_mul_ps(x, _mm_set1_ps(1.4426950408889634f)));
}

int main(){
    __m128 a;
    float *f = (float*)&a, x, error, relative_error, max_relative_error = 0;

    for (x = -88; x <= 88; x += 0.125f){
        f[0] = x;
        a = my_exp(a);
        error = exp(x) - f[0];
        relative_error = error / exp(x);
        if (relative_error > max_relative_error) max_relative_error = relative_error;
    }

    printf("max relative error: %f\n", max_relative_error);

    return 0;
}
