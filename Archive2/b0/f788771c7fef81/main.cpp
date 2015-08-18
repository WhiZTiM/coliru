#include <iostream>
#include <typeinfo>
#include <utility>

template<class... Ts>
struct type_list {};

template<class T>
struct type {
    using t = T;
};


template<class... Ts, class F>
void for_each_type(type_list<Ts...>, F&& f)
{
    auto x = {(f(type<Ts>()), true)...};
    (void)x;
}

int main()
{
    for_each_type(type_list<short, double>(),
                  [](auto x) {
                      std::cout << typeid(decltype(x)).name() << std::endl;
                  });
    return 0;
}