#include <initializer_list>
#include <iostream>

namespace
{
    enum class Type
    {
        PLUS,
        MINUS
    };
    
    int valueSelector(const std::initializer_list<int>& pars, Type type)
    {
        auto it = pars.begin();
        int a = *(it++);
        int b = *(it++);
        switch(type)
        {
            case Type::PLUS: return a + b;
            case Type::MINUS: return a - b;
            default: throw "Unknown value combinaiton type";
        }
    }
    
    class Foo
    {
    public:
         
         Foo() = delete;
         
         Foo(const std::initializer_list<int>& pars, Type type = Type::PLUS): m_value(valueSelector(pars, type))
         {}
         
     private:
     
        int m_value;
        
        friend std::ostream& operator << (std::ostream& os, const Foo&);
    };
    
    std::ostream& operator << (std::ostream& os, const Foo& x)
    {
        os << "{" << x.m_value << "}";
        return os;
    }
    
}

int main()
{
    Foo x{3,5};
    Foo y{{3,5}, Type::PLUS};
    Foo z{{3,5}, Type::MINUS};
    
    std::cout << x << " " << y << " " << z << std::endl;
    
    return EXIT_SUCCESS;
}