#include <functional>
#include <iostream>

class test_class
 
int f(int a) { return -a; }
int main()
{
    // fn1 and fn2 have the same type, but their targets do not
    std::function<int(int)> fn1(f),
                            fn2([](int a) {return -a;});
    std::cout << fn1.target_type().name() << '\n'
              << fn2.target_type().name() << '\n';
}