#include <string>
#include <iostream>
#include <iomanip>
#include <typeinfo>

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

#define DEBUG_TYPE(x) do { typedef void(*T)(x); debug_type<T>(T(), (#x)); } while(0)

template<typename T>
struct debug_type
{
    template<typename U>
    debug_type(void(*)(U), const std::string& p_str)
    {
        std::string str(p_str.begin(), p_str.end());
        std::cout << str << " => ";
        #ifndef _MSC_VER
        char * name = 0;
        int status;
        name = abi::__cxa_demangle(typeid(U).name(), 0, 0, &status);
        if (name != 0) { std::cout << name << std::endl; free(name);}
        else
        #endif
        { std::cout << typeid(U).name() << std::endl; }
    }
};

typedef char MyChar;

namespace test {
    typedef int MyInt;
    
    struct MyStruct {};
    class MyClass {};
}

using test::MyInt;
using test::MyClass;

int main()
{
    DEBUG_TYPE(char);
    DEBUG_TYPE(int);
    DEBUG_TYPE(float);
    DEBUG_TYPE(MyChar);
    DEBUG_TYPE(test::MyInt);
    DEBUG_TYPE(MyInt);
    DEBUG_TYPE(test::MyStruct);
    DEBUG_TYPE(MyClass);
    return 0;   
}
