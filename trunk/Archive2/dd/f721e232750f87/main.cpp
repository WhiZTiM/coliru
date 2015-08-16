#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <functional>
#include <utility>
#include <cstddef>

// The stolen function_traits struct...thing
template<typename T>
struct function_traits;

template<typename R, typename ...Args>
struct function_traits<std::function<R(Args...)>>
{
    static const size_t nargs = sizeof...(Args);

    using result_type = R;

    template <size_t i>
    struct arg
    {
        using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
};

int foo(float x, double d)
{
    return int(x);
}

template <size_t argIdx, typename R, typename... Args>
auto getArgTypes(std::string& ref) 
    -> typename std::enable_if<argIdx == 1>::type
{
    using fun = function_traits<std::function<R(Args...)> >;
    ref.append(typeid(typename fun::template arg<0>::type).name()).append(" ");
}

template <size_t argIdx, typename R, typename... Args>
auto getArgTypes(std::string& ref) 
    -> typename std::enable_if<argIdx != 1>::type
{
    using fun = function_traits<std::function<R(Args...)> >;
    ref.append(typeid(typename fun::template arg<argIdx-1>::type).name()).append(" ");
    getArgTypes<argIdx - 1, R, Args...>(ref);
}

template <typename F, std::size_t... Is>
void test2(std::index_sequence<Is...>)
{
    std::string s;
    getArgTypes<F::nargs, typename F::result_type, typename F::template arg<Is>::type...>(s);
    
    std::cout << s;
}

void test()
{
    using F = function_traits<std::function<decltype(foo)>>;
    test2<F>(std::make_index_sequence<F::nargs>{});
}

int main()
{
    test();
}
