#include <type_traits>
#include <iostream>

struct A { void foo(size_t) const; };
struct B { void foo(size_t); };
struct C {};

namespace detail{
    template<class T>struct tag{using type=T;};
    template<class T, class... Args>
    using return_t=decltype(std::declval<T&>().foo(std::declval<Args>()...));
    template<class Sig>
    struct method_sig;
    template<class Sig>
    using method_sig_t=typename method_sig<Sig>::type;
    template<class C, class... Args>
    struct method_sig<C(Args...)>:tag<std::conditional_t<
        std::is_const<C>::value,
        return_t<C, Args...>(C::*)(Args...) const,
        return_t<C, Args...>(C::*)(Args...)
    >> {};
}

template<class Sig, class T>
constexpr bool has_method(T) { return false; }
template<class Sig, class = detail::method_sig_t<Sig>>
constexpr bool has_method(detail::method_sig_t<Sig>) { return true; }

int main() {
    static_assert(has_method<const A(size_t)>(&A::foo)); // Good
    static_assert(!has_method<A(size_t)>(&A::foo)); // Good
    static_assert(has_method<B(size_t)>(&B::foo)); // Good
    static_assert(!has_method<C(size_t)>(&C::foo)); // Bad, doesn't compile!
}