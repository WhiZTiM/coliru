#include <utility>

template<class... Ts>
struct type_list {};

template<class T>
struct type {
    using t = T;
};

template<class... Ts>
constexpr void noop(Ts&&...)
{
}

template<class... Ts, class F>
void for_each_type(type_list<Ts...>, F&& f)
{
    noop((f(type<Ts>()), 0)...);
}

int main()
{
    for_each_type(type_list<short, double>{},
                  [](auto) {});
    return 0;
}