#include <iostream>
#include <boost/lexical_cast.hpp>
 
int main()
{
    const wchar_t* s1 = L"124";
    long num = boost::lexical_cast<long>(s1);
    std::cout << num;
    try
    {
        const wchar_t* s2 = L"not a number";
        long num2 = boost::lexical_cast<long>(s2);
        std::cout << num2 << "\n";
    }
    catch (const boost::bad_lexical_cast& e)
    {
        std::cout << e.what();
    }
}