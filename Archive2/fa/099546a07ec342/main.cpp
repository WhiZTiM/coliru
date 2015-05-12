#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_same<T, int>::value, void>::type to_string(const T&) { return; }


template<typename T, typename U=void>
struct HasToString : std::false_type {
};

template<typename T>
struct HasToString<T, decltype(to_string<T>(std::declval<T>()))> : std::true_type {
};


int main()
{
    static_assert(HasToString<int>::value, "int has to have a ToString");
    static_assert(!HasToString<float>::value, "int has to have a ToString");
}
