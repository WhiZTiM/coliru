

#include <iostream>
#include <vector>


class A 
{
public:
    A() 
    {   
        std::cout << "A ctor\n";
    }
    
    //Declaration of copy constructor
    A(const A& other)
    {
        std::cout << "copy constructor\n";
    }
    
    ~A()
    {
        std::cout << "A dtor\n";
    }
};

void f( std::vector<A> a )
{
}

int main()
{
    std::vector<A> v;
    
    //With a created is a destructor is not called
    A a;
    v.push_back(a);
    
    std::cout << "nya\n";
    
    f(v);
    
    std::cout << "after vector created\n";
    v.push_back(A());
    std::cout << "after one A added\n";
}