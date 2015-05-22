#include <iostream>
#include <type_traits>
#include <string>

inline
void Check(const auto& result)
{
    std::cout << (std::is_signed<decltype(result)>::value ? "signed result   : " : "unsigned result : ");
    std::cout << result << std::endl;
}

int main() 
{
    int t1 = 12;
    unsigned long long t2 = 30ull;
    std::string str1 = "test";
    
    Check(t1);
    Check(t2);
    Check(str1);
}
