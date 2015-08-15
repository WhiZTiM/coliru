#include <type_traits>
#include <utility>
#include <stddef.h>

template <typename CharType, size_t Size>
class StringT {};

template <typename S, typename C>
struct IsStringT : std::false_type {};

template <typename C, size_t Size>
struct IsStringT<StringT<C, Size>, C> : std::true_type {};

template <typename T>
void GetProperty(T & val)
{
    static_assert(IsStringT<typename std::remove_cv<T>::type, char>{}, "FAILED");
}

template <>
void GetProperty<bool>(bool & val) {}

template <>
void GetProperty<int>(int & val) {}

int main()
{
    StringT<char, 512> str1;
    GetProperty(str1);
    
    StringT<char, 1024> str2;
    GetProperty(str2);
}
