#include <iostream>

class A
{
public:
    A() : value(0.) {}
    A(double d) : value(d) {}
    double get() const { return value; }
    A& operator *= (const A& tmp)
    {
        value *= tmp.value;
        return *this;
    }
    operator double() const
    {
        return value;
    }
private:
    double value;
};

A operator * (const A& lhs, const A& rhs)
{
    A tmp = lhs;
    tmp *= rhs;
    return tmp;
}

int main()
{
    A a(1.), b(2.);
    double c = a * b;
    std::cout << c << std::endl;
    A d = c;
    std::cout << d.get() << std::endl;
}