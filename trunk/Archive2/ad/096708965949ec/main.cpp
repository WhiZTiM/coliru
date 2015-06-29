#include <iostream>
#include <utility>

#define MAKE_WRAPPER(decl) \
    template <typename F, typename ...Args>                             \
    decl                                                                \
{                                                                       \
    std::cout << "WRAPPER: BEFORE" << std::endl;                        \
    auto && res = std::forward<F>(f)(std::forward<Args>(args)...);      \
    std::cout << "WRAPPER: AFTER" << std::endl;                         \
    return res;                                                         \
}

MAKE_WRAPPER(typename std::result_of<F &&(Args &&...)>::type wrapper1(F && f, Args &&... args))
MAKE_WRAPPER(         std::result_of_t<F &&(Args &&...)>     wrapper2(F && f, Args &&... args))
MAKE_WRAPPER(decltype(auto)                                  wrapper3(F && f, Args &&... args))

int & dummy(int & a)
{
    return a;
}

int main(void)
{
    int n = 10;

    wrapper1(dummy, n) *= 2;
    wrapper2(dummy, n) *= 2;
    wrapper3(dummy, n) *= 2;

    std::cout << n << std::endl;
}