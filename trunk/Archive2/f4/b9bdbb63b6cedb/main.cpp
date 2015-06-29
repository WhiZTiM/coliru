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
    
    template<typename T>
    using identity = T;

    template<typename...>
    struct voider { using type = void; };
    template<typename... Ts> using void_t = typename voider<Ts...>::type;

    template<class Sig, method_sig_t<Sig>>
    struct has_method : std::true_type {};
    // Cannot do specialization for false_type
}

int main() {
    static_assert(detail::has_method<const A(size_t), &A::foo>{}); // const version works
    //static_assert(detail::has_method<A(size_t), &A::foo>{}); // cannot compile!
}