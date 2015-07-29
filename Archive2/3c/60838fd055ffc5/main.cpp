#include <iostream>

class Type;

namespace MyNamespace {
    template<class T>
    const Type& get_Type(T*);
}

#define GET_TYPE(type) MyNamespace::get_Type( (type *) 0)

class Type
{
public:
    Type(int val) : m_val(val) {}
    int m_val;    
};

//namespace MyNamespace {
//    template<>
//    const Type& get_Type(int*);
//}

int function()
{
    const Type& type = GET_TYPE(int);
    return type.m_val;
}

namespace MyNamespace
{
    //template<>
    const Type& get_Type(int*) 
    { 
        static Type intType(1);
        return intType;
    }
}

int main()
{
    std::cout << function();
}