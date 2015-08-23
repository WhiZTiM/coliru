#include <iostream>
#include <immintrin.h>

class Vec4d {
public:
    Vec4d(double v0, double v1, double v2, double v3) : data(_mm256_setr_pd(v3,v2,v1,v0)) {}
    Vec4d(__m256d data) : data(data) {}
    
    friend Vec4d operator+(Vec4d a, Vec4d b) {
        return Vec4d(_mm256_add_pd(a.data, b.data));
    }
    
    double operator[](unsigned i) {
        double *p = (double*)&data;
        return p[i];
    }
	
private:
	__m256d data;
};

int main() {
	Vec4d u(0,1,2,3);
    Vec4d v(1,1,1,1);
    Vec4d w = u+v;
    
    for (int i = 0; i < 4; i++) {
        std::cout << w[i] << " ";
    }
    std::cout << std::endl;
    
	return 0;
}