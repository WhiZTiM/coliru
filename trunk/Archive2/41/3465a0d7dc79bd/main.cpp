#include <functional>
#include <iostream>

template<typename R, typename... Args>
struct function_type
{
    using type = std::function<R(Args...)>;  
};

template <typename R, typename... Args>
R call_with( typename function_type<R, Args...>::type f,
            Args... args)
{
    return f(args...);
}

int main()
{
    call_with<void>([](int){ std::cout << "called" << std::endl; }, 2);
}
