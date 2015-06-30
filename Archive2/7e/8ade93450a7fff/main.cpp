#include <iostream>
#include <cmath>
using namespace std;

class A
{ 
private:
    int foo;
    int bar;
    double foobar;
public:
    A(int a, int b, double c) : foo(a), bar(b), foobar(c) {}
    
};

void myFunc(A a){ }

int main(){
    myFunc(A{1,2,3.0});
    return 0;
}