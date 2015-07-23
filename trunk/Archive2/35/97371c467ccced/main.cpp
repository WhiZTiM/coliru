#include <iostream>
#include <type_traits>
#include <utility>

template<class T>
struct tag {
    using type=T;
    constexpr tag(tag const&) = default;
    constexpr tag() = default;
    template<class U,
        class=std::enable_if_t<std::is_base_of<T,U>{}>
    >
    constexpr tag(tag<U>) {}
};

struct Base{};
struct Derived:Base{};

template<class T>
void foo( T t, tag<Base> =tag<T>{} ) {
}


int main(){
    foo(Derived{});
}