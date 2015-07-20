#include <vector>
#include <string>
#include <iostream>
 
class A
{
public:
    A(int i)
    {
        m_i = i;
        std::cout << "constructor of A" << '\n';
    }
    
    A(A& other)
    {
        std::cout << "copy constructor of A" << '\n';
    }
    

    A(A&& other) noexcept
    {
        std::cout << "move constructor of A" << '\n';
    }

    
    int m_i;
};
 
A GetA()
{
    A a(10);
    return a;
}

int main() 
{
    A a = GetA();
}