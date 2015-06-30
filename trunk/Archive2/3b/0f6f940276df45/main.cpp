#include <iostream>
 
class C
{
public:
    int f() const;
private:
    int value = 42;
};
 
auto C::f() const -> decltype(value) { return value; }
 
 
int main()
{
    C c;
 
    std::cout << c.f() << std::endl;
}