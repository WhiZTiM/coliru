#include <iostream>

typedef long integer;

class A {
  public:
    
    template <typename T>
    operator T*() { return NULL; }

};

int main() {
    A a;
    int *ip = a;
    long *lp = a;
    std::cout << "All good...\n";
    return 0;
}
