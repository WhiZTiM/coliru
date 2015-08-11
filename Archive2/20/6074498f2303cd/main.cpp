#include <iostream>
#include <utility>

template <typename T>
struct member_function_traits;

template <typename C, typename R, typename... Args>
struct member_function_traits<R(C::*)(Args...)> {
    using return_type = R;

    template <std::size_t i>
    struct param
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};

template<typename Functor>
struct functor_traits {
    using return_type = typename member_function_traits<decltype(&Functor::operator())>::return_type;
    
    template<std::size_t i>
    using param = typename member_function_traits<decltype(&Functor::operator())>::template param<i>;
};

struct functor {
    void operator()(int) {}
};

int main() {
    std::cout << std::is_same<functor_traits<functor>::return_type, void>::value << std::endl;
    std::cout << std::is_same<functor_traits<functor>::param<0>::type, int>::value << std::endl;
}
