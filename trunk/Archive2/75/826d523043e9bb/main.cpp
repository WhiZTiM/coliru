struct JInt { };

struct JBool { };

namespace detail
{

template<typename T>
struct java_type_to_cpp_type;

template<>
struct java_type_to_cpp_type<JInt>
{
    using type = int;
};

template<>
struct java_type_to_cpp_type<JBool>
{
    using type = bool;
};

}

template<typename T>
using java_type_to_cpp_type = typename detail::java_type_to_cpp_type<T>::type;

// ...

#include <iostream>

int main()
{
    java_type_to_cpp_type<JInt> x = 42;
    std::cout << x;
}