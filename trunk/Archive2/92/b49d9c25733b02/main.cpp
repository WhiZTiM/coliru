#include <iostream>

typedef long integer;

class A {
  public:
    
    template <typename T>
    operator T*() { return NULL; }

};

struct foo {};

int main() {
    A a;
    
    int *ip = a;
    long *lp = a;
    integer *Ip = a;
    double *dp = a;
    foo *fp = a;
    
    std::cout << "All good...\n";
    return 0;
}
