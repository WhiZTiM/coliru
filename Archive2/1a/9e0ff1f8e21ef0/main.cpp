#include <iostream>
#include <cwchar>

int main()
{
    const wchar_t* s1  = L"123";
    wchar_t *end;
    long long1 = std::wcstol(s1, &end, 10);
    if (s1 != end && errno != ERANGE)
    {
        std::cout << long1;
    }
    else
    {
        std::cout << "Error";
    }
    const wchar_t* s2  = L"not a number";
    long long2 = std::wcstol(s2, &end, 10);
    if (s2 != end && errno != ERANGE)
    {
        std::cout << long2;
    }
    else
    {
        std::cout << "Error";
    }
}