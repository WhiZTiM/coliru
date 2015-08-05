#include <iostream>

struct Base
{
    Base() = default;
    
    Base(int x_, int y_ = 88, int z_ = 99)
        : x(x_), y(y_), z(z_) {}
    
    virtual void debug() const 
    { std::cout << "\nx - " << x << ", y - " << y << ", z - " << z << '\n'; } 
    
private:
    int x, y, z;
};

struct Derived : Base
{
    using Base::Base;
};

int main() {
    Base B(1);
    B.debug();
    Derived D(5);
    D.debug();
    
    return 0;
}