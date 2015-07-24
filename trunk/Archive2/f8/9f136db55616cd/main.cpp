#include <type_traits>

template <class T>
struct function_traits
{
    typedef typename function_traits<
        decltype(&T::operator())
    >::return_type return_type;
};

template <class R, class C, class ...Args>
struct function_traits<R (C::*)(Args...)>
{
    typedef R return_type;
};

template <class R, class ...Args>
struct function_traits<R (*)(Args...)>
{
    typedef R return_type;
};

int main()
{
    auto i = 0;
    auto testingLambda = [i](int a) mutable { ++i; return 1LL * a; };
    typename function_traits<decltype(testingLambda)>::return_type test;
    
    static_assert(std::is_same<decltype(test), long long>{}, "");
}