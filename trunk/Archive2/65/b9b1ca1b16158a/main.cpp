template<class T, class U>
T&& fwd(U&& v) { return static_cast<T&&>(v); }

template<class F, class T, class Final>
struct fold_helper
{
    F& f;
    T&& value;
    
    constexpr T&& get() { return fwd<T>(value); }
    constexpr Final final() { return fwd<T>(value); }
};

template<class Final, class F, class T>
constexpr fold_helper<F, T, Final> make_helper(F& f, T&& v){ return { f, fwd<T>(v) }; }

template<class F, class T, class U, class _1, class _2>
constexpr decltype(auto) operator,(fold_helper<F, T, _1> lhs, fold_helper<F, U, _2> rhs)
{
    return make_helper<decltype(lhs.f(lhs.get(), rhs.get()))>(lhs.f, lhs.f(lhs.get(), rhs.get()));
}

template<class F, class T, class... Ts>
constexpr decltype(auto) foldl(F&& f, T&& v, Ts&&... vs)
{
    return (make_helper<T&&>(f, fwd<T>(v)), ..., make_helper<Ts&&>(f, fwd<Ts>(vs))).final();
}

template<class F, class T, class... Ts>
constexpr decltype(auto) foldr(F&& f, T&& v, Ts&&... vs)
{
    return (make_helper<Ts&&>(f, fwd<Ts>(vs)), ..., make_helper<T&&>(f, fwd<T>(v))).final();
}

#include <iostream>

template<class> struct dump;

int main()
{
    auto min = [](int a, int b) { return (a < b ? a : b); };
    //dump<decltype(foldl(min, 5, 3, 8, 2))>{}; // == dump<int>, so, value type
    std::cout << foldl(min, 5, 3, 8, 2) << "\n"; // "0" ?!?!
    std::cout << foldr(min, 5, 3, 8, 2) << "\n"; // 2
}