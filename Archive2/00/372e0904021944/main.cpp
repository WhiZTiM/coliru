#include <iostream>
#include <type_traits>

inline
void Check(const auto& result)
{
    std::cout << (std::is_signed<decltype(result)>::value ? "signed result   : " : "unsigned result : ");
    std::cout << result << std::endl;
}

int main() 
{
    auto t1 = 10u;
    auto t2 = -15;
    
    Check(t1 - t2);
    Check(t2 - t1);
}
