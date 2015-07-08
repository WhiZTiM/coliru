#include <iostream>

class T {
  public:
    T(const T&  o) { std::cout << "T(T)"  << std::endl; }
    T(      T  *o) { std::cout << "T(T*)" << std::endl; }
};

void test()
{
    T *val = 0;
    {
        T val(val);
    }
}

int main()
{
    test();
}