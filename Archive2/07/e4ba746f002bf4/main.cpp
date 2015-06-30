#include <iostream>
#include <cmath>
using namespace std;

class A{ /*... snip ...*/ };

void myFunc(A a){ }

int main(...){
    myFunc(A{});
    return 0;
}