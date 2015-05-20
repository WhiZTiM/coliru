#include <iostream>
#include <type_traits>
#include <ctime>
#include <cstdlib>



class Foo
{
public:
    Foo() { std::cout << "Called default" << std::endl; }
    Foo(int) { std::cout << "Called new" << std::endl; }
};

Foo const Bar()
{
    return 12;    
}

int main()
{
    std::srand(std::time(0));
    bool dontOptimizeMe = std::rand() % 2;
    
    std::decay<decltype( Bar() )>::type Obj1;
    if (dontOptimizeMe) {
        std::cout << "Entered the IF" << std::endl;
        Obj1 = Foo(10);    
    }
    else {
        std::cout << "Entered the ELSE" << std::endl;
        Obj1 = Foo();
    }
}