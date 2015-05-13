#include <string>

template<typename T, typename U=void>
struct HasToString : std::false_type {
};

template<typename T>
struct HasToString<T, 
    decltype(std::to_string(std::declval<T>()))> : std::true_type {
};


int main()
{
    static_assert(HasToString<int>::value, "oops");
}