#include <boost/optional.hpp>
#include <iostream>

int
main()
{
    enum class Foo {
        kZero = 0,
        kOne = 1,
    };
    
    boost::optional<Foo> optionalFoo;
    
    if (optionalFoo == Foo::kZero) {
        std::cout << "optional foo is kZero!" << std::endl;
    } else {
        std::cout << "optional foo is NOT kZero!" << std::endl;
    }
 
    return 0;
}