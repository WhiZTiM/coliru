#include <iostream>
#include <utility>

template <typename T>
struct member_function_traits;

template <typename C, typename R, typename P>
struct member_function_traits<R(C::*)(P)> {
    using return_type = R;
    using param_type = P;
};

template<typename Functor>
struct functor_traits {
    using return_type = typename member_function_traits<decltype(&Functor::operator())>::return_type;
    using param_type = typename member_function_traits<decltype(&Functor::operator())>::param_type;
};

struct functor {
    void operator()(int) {}
};

int main() {
    std::cout << std::is_same<functor_traits<functor>::return_type, void>::value << std::endl;
    std::cout << std::is_same<functor_traits<functor>::param_type, int>::value << std::endl;
}
