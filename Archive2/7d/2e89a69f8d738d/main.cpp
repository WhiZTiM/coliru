#include <functional>
#include <iostream>

template <typename R, typename... Args>
R call_with(std::function<R(Args...)> f,
            Args... args)
{
    return f(args...);
}

int main()
{
    call_with<void>([](int){ std::cout << "called" << std::endl; }, 2);
}
