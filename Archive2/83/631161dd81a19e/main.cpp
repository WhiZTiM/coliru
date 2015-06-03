template<class T, class U>
T&& fwd(U&& v) { return static_cast<T&&>(v); }

template<class F, class T>
struct fold_helper
{
    F& f;
    T&& value;
    
    constexpr T&& get() { return fwd<T>(value); }
};

template<class F, class T>
constexpr fold_helper<F, T> make_helper(F& f, T&& v){ return { f, fwd<T>(v) }; }

template<class F, class T, class U>
constexpr decltype(auto) operator,(fold_helper<F, T> lhs, fold_helper<F, U> rhs)
{
    return make_helper(lhs.f, lhs.f(lhs.get(), rhs.get()));
}

template<class F, class T, class... Ts>
constexpr decltype(auto) foldl(F&& f, T&& v, Ts&&... vs)
{
    return (make_helper(f, fwd<T>(v)), ..., make_helper(f, fwd<Ts>(vs))).get();
}

/*
template<class F, class... Ts>
constexpr decltype(auto) foldl1(F&& f, Ts&&... vs)
{
    return (..., make_helper(f, fwd<Ts>(vs))).get(); // lolz bug: "error: expected ';' after return statement"
}
*/

template<class F, class T, class... Ts>
constexpr decltype(auto) foldr(F&& f, T&& v, Ts&&... vs)
{
    return (make_helper(f, fwd<Ts>(vs)), ..., make_helper(f, fwd<T>(v))).get();
}

template<class F, class... Ts>
constexpr decltype(auto) foldr1(F&& f, Ts&&... vs)
{
    return (make_helper(f, fwd<Ts>(vs)), ...).get();
}

#include <iostream>

int main()
{
    std::cout << foldl([](int a, int b){ return (a < b ? a : b); }, 5, 3, 8, 2) << "\n"; // "0" ?!?!
    //std::cout << foldl([](int a, int b){ return (a < b ? a : b); }, 5, 3, 8, 2) << "\n"; // lolz bug
    std::cout << foldr([](int a, int b){ return (a < b ? a : b); }, 5, 3, 8, 2) << "\n"; // 2
    std::cout << foldr1([](int a, int b){ return (a < b ? a : b); }, 5, 3, 8, 2) << "\n"; // 2
}