#include <iostream>

#define clreflect_function_overload(name, ret, ...) const auto& name##_alias = static_cast<ret(*)__VA_ARGS__>(name);
#define clreflect_function(...) const auto& mul_alias = __VA_ARGS__;

int add(int, int);
int add(int a, int b)
{
    return a + b;
}

template<typename T>
T mul(T a, T b)
{
    return a * b;
}

int sub(int a, int b)
{
    return a - b;
}

unsigned sub(unsigned a, unsigned b)
{
    return a - b;
}

namespace hidden
{
    clreflect_function_overload(sub, unsigned, (unsigned a, unsigned b))
    const auto& add_alias = add;
    //const auto& sub_alias = sub;
    //const auto& mul_alias = mul<unsigned>;
    clreflect_function(mul<unsigned>)
}

int main()
{
    unsigned mul_result = mul<unsigned>(4, 5);
    unsigned mul_alias_result = hidden::mul_alias(4,5);
    unsigned sub_result = sub(10,5);
    unsigned sub_alias_result = hidden::sub_alias(10,5);
    
    
    
    
    std::cout << "mul: " << mul_result << std::endl;
    std::cout << "mul_alias: " << mul_alias_result << std::endl;
    
    std::cout << "sub: " << sub_result << std::endl;
    std::cout << "sub_alias: " << sub_alias_result << std::endl;
    
    hidden::add_alias(2,3);
    return 0;
}
