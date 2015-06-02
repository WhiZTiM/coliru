#include <iostream>

int main()
{
    void* v = nullptr;
    int* i0 = static_cast<int*>(v);
    (void) i0;
    
    /*
    double* d1 = nullptr;
    int* i1 = static_cast<int*>(d1); //peta
    (void) i1;
    */
    
    double* d2 = nullptr;
    int* i2 = reinterpret_cast<int*>(d2); //se lo traga.
    (void) i2;
}
