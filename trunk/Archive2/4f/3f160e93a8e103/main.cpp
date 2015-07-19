#include <iostream>

class A{
    const static int p = 1;
    class B {
        friend void f() {
            std::cout << p << '\n';
            std::cout << q << '\n';
        }
    };
public:
    const static int q = 2;
};
void f();
    
int main()
{
    f();
}
