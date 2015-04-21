#include <stdio.h>
#include <stdlib.h>
#include <type_traits>
#include <utility>

namespace details
{
    
    struct impl_has_foo
    {
        template <typename> static std::false_type sfinae(...);
        template <typename T> static std::true_type sfinae(std::result_of_t<decltype(&T::foo)(T, int, char)> *);
    };
    
    template <typename T>
    struct has_foo : decltype(impl_has_foo::sfinae<T>(nullptr)) {};
    
    template <typename T, bool = has_foo<T>::value>
    struct example
    {
        example()
        {
            T t;
            t.foo(1, 'a');
        }
    };
    
    template <typename T>
    struct example<T, false>
    {
        static_assert(has_foo<T>::value, "Provided type doesn't have foo member function");
    };
}

template <typename T>
struct example : public details::example<T> {};

struct test
{
    int foo(int, char) { return 0; }
};

int main(int argc, char *argv[]) 
{
  example<int> test;
  return 0;
}