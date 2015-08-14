#include <iostream>
#include <string>
 
int main()
{
    const wchar_t* s1 = L"45";
    const wchar_t* s2 = L"not a long";
 
    long long1 = std::stol(s1);
    std::cout << long1 << "\n";
    try
    {
        long long2 = std::stol(s2);
        std::cout << long2;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << e.what();
    }    
}