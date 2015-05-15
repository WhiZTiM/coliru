#include <boost/type_index.hpp>
#include <functional>
#include <iostream>

struct base { virtual ~base(){} };
struct derived { int foo(int) { return 0; } };
 
int f(int a) { return -a; }
int main()
{
    derived d;
    
    // fn1 and fn2 have the same type, but their targets do not
    std::function<int(int)> fn1(f),
                            fn2([](int a) {return -a;}),
                            fn3(std::bind(&derived::foo, &d, 0));
                            
    using boost::typeindex::type_index;
    std::cout << type_index(fn1.target_type()).pretty_name() << '\n'
              << type_index(fn2.target_type()).pretty_name() << '\n'
              << type_index(fn3.target_type()).pretty_name() << '\n'
              << '\n'
              << type_index(fn1.target_type()).raw_name() << '\n'
              << type_index(fn2.target_type()).raw_name() << '\n'
              << type_index(fn3.target_type()).raw_name() << '\n';
}