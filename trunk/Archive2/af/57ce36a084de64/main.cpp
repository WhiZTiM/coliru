#include <iostream>
#include <type_traits>
#include <string>

template < typename T1, typename T2 = void >  
struct TestT  
{  
    static const bool is_int = false;  
    static const bool is_str = false;  
};

template < typename T>  
struct TestT<T, std::enable_if_t<std::is_arithmetic<T>::value>>  
{  
    static const bool is_int = true;  
    static const bool is_str = false;  
};  

template <>
struct TestT<std::string>  
{  
    static const bool is_int = false;  
    static const bool is_str = true;  
};  

enum class TestE  
{  
    Last  
};

int main()  
{
    std::cout << "Enum is_int: " << TestT<TestE>::is_int  
              << ", is_str: " << TestT<TestE>::is_str << std::endl;  
    std::cout << "string is_int: " << TestT<std::string>::is_int  
              << ", is_str: " << TestT<std::string>::is_str << std::endl;  
    std::cout << "int is_int: " << TestT<int>::is_int  
              << ", is_str: " << TestT<int>::is_str << std::endl;  
    return 0;
}  