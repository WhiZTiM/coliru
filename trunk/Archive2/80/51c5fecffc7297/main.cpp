#include <iostream>
#include <math.h>  
#include <iomanip>

int main(){
    const int n=1000000;
    int i=0;
    double x=0;
    for (i=0; i<n; i++) x+=i;
    std::cout<< std::setprecision(10) << log(x) << std::endl;
    return 0;
}