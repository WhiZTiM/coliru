#include <iostream>

int main()
{
    int thei = 123;
    int* intp = &thei;
    double thed = thei;
    double* doublep = &thed;
    
    //int to int*
    intp = static_cast<int*>(thei);
    intp = reinterpret_cast<int*>(thei);
    
    //int* to int
    thei = static_cast<int>(intp);
    thei = reinterpret_cast<int>(intp);
    
    //int* to double*
    doublep = static_cast<double*>(intp);
    doublep = reinterpret_cast<double*>(intp);
    
    return 0;
}
