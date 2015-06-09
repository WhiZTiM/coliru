#include <functional>
#include <type_traits>

template<typename T>
struct protect_wrapper : T
{
    protect_wrapper(const T& t) : T(t)
    {}
    
    protect_wrapper(T&& t) : T(std::move(t))
    {}
};

template<typename T>
std::enable_if_t<!std::is_bind_expression<std::decay_t<T>>::value,
                 T&&
                >
protect(T&& t)
{
    return std::forward<T>(t);
}

template<typename T>
std::enable_if_t<std::is_bind_expression<std::decay_t<T>>::value,
                 protect_wrapper<std::decay_t<T>>
                >
protect(T&& t)
{
    return protect_wrapper<std::decay_t<T>>(std::forward<T>(t));
}

template<typename HandlerType>
void call_handler(HandlerType&& handler)
{
  handler();
}

template<typename HandlerType>
void do_something(HandlerType&& handler)
{
  auto f = std::bind(
    &call_handler<HandlerType&>,
    std::forward<HandlerType>(handler));
  f();
}

int main()
{
  auto a = [&]() {};
  do_something(a);
  do_something(std::move(a));

  auto b = protect(std::bind([&]() {}));
  do_something(b);
  do_something(std::move(b));
}
