#include <iostream>

class Wrap
{
public:
    Wrap(int n = 0) : num(n) {} //ctor
    ~Wrap() {} //dtor
    
    void operator==(const Wrap& rhs)
    {
        return;
    }
    
    friend bool operator==(const Wrap& lhs, const Wrap& rhs);
    
private:
    int num;
    
};

bool operator==(const Wrap& lhs, const Wrap& rhs)
{
    return lhs.num == rhs.num;
}

int main()
{
    Wrap foo(1);
    Wrap bar(2);
    
    if (foo == bar)
        std::cout << "Foo == bar!" << std::endl;
    else
        std::cout << "Foo is not bar" << std::endl;

    return 0;
}