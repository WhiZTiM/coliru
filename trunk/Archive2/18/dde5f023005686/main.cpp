#include <type_traits>

template <typename T>
struct B {};

template <typename T>
struct is_b : std::false_type {};

template <typename T>
struct is_b<B<T>> : std::true_type {};

template <typename T>
struct is_b<const B<T>> : std::true_type {};

template <typename T, typename Enable = void>
struct A {};

template <typename T>
struct A<T, typename std::enable_if<is_b<T>{}>::type> {};

int main()
{
    
}
