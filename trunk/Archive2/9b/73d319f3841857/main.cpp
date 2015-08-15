#include <type_traits>
#include <utility>
#include <stddef.h>

template <typename CharType, size_t Size>
class StringT {};

template <typename S>
struct IsCharStringT : std::false_type {};

template <size_t Size>
struct IsCharStringT<StringT<char, Size>> : std::true_type {};

template<typename T>
void GetProperty(T & val)
{
    static_assert(IsCharStringT<T>{}, "FAILED");
}

template<>
void GetProperty<bool>(bool & val)
{
    // Do stuff
}

template<>
void GetProperty<int>(int & val)
{
    // Do stuff
}

int main()
{
    StringT<char, 512> str1;
    GetProperty(str1);
    
    StringT<char, 1024> str2;
    GetProperty(str2);
}
