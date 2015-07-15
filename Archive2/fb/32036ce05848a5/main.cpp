#include <functional>
#include <iostream>

// identity is a useful meta-function to have around.
// There is no std::identity, alas.
template< typename T>
struct identity
{
    using type = T;
};

template <typename R, typename... Args>
R call_with( typename identity<std::function<R(Args...)>>::type f,
            Args... args)
{
    return f(args...);
}

int main()
{
    call_with<void>([](int){ std::cout << "called" << std::endl; }, 2);
}
