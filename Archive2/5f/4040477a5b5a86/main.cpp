#include <type_traits>

template <class T>
struct function_traits
{
    typedef typename function_traits<
        decltype(&T::operator())
    >::return_type return_type;
};

template <class R, class ...Args>
struct function_traits<R (*)(Args...)>
{
    typedef R return_type;
};

template <class R, class F, class ...Args>
struct function_traits<R (F::*)(Args...)>
{
    typedef R return_type;
};

template <class R, class F, class ...Args>
struct function_traits<R (F::*)(Args...) const>
{
    typedef R return_type;
};

int main()
{
    auto testingLambda = [](int a) { return 1LL * a; };
    typename function_traits<decltype(testingLambda)>::return_type test;
    
    static_assert(std::is_same<decltype(test), long long>{}, "");
}