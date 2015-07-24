#include <iostream>
#include <new>

struct A
{
  int t;
};

int main()
{
    char *buf = new char[sizeof(A)];
    
    A* ptr = new (buf) A;
    ptr->t = 1;
    
    // Also valid, because points to an actual constructed A!
    A *ptr2 = reinterpret_cast<A*>(buf);
    std::cout << ptr2->t;
}