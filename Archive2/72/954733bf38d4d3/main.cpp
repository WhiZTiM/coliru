template<class F, class... Fs>
struct overload_set : F, overload_set<Fs...>
{
    overload_set(F f, Fs... fs)
        : F(f), overload_set<Fs...>(fs...) {}

    using F::operator();
    using overload_set<Fs...>::operator();
};

template<class F>
struct overload_set<F> : F
{
    overload_set(F f) : F(f) {}
    
    using F::operator();
};

template<class... Fs>
overload_set<Fs...> overload(Fs... fs){ return { fs... }; }

template<class T> struct identity { using type = T; };

#include <iostream>

struct X
{
    void f();
};

struct Y
{
};

int main()
{
    auto l1 = [](auto x, int) -> decltype(std::declval<typename decltype(x)::type>().f(), void()) { std::cout << "has f()\n"; };
    auto l2 = [](auto, long) { std::cout << "doesn't have f()\n"; };
    
    auto set = overload(l1, l2);
    set(identity<X>{}, 0);
    set(identity<Y>{}, 0);
}