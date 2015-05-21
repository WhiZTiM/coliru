#include <functional>
#include <utility>

template<typename...> struct void_t_impl { using type = void; };
template<typename... Ts> using void_t = typename void_t_impl<Ts...>::type;
template<typename Signature, typename = void> struct is_invokable : std::false_type {};
template<typename F, typename... Args> struct is_invokable<F(Args...), void_t<decltype(std::declval<F>()(std::declval<Args>()...))>> : std::true_type {};

template<typename Signature> struct function_pointer;
template<typename R, typename... Args> struct function_pointer<R(Args...)> { using type = R(*)(Args...); };

template<typename Sig1, typename Sig2>
class multifunction {
    using f1_t = std::function<Sig1>;
    using f2_t = std::function<Sig2>;

    using fp1_t = typename function_pointer<Sig1>::type;
    using fp2_t = typename function_pointer<Sig2>::type;

public:
    template<typename F>
    multifunction(F&& f) : f1{std::forward<F>(f)}, f2{std::forward<F>(f)} {};
    
    multifunction(fp1_t fp1, fp2_t fp2) : f1{fp1}, f2{fp2} {};

    template<typename... Args>
    auto operator()(Args&&... args) {
        return invoke(is_invokable<f1_t(Args...)>{}, is_invokable<f2_t(Args...)>{}, std::forward<Args>(args)...);
    }
    
private:
    f1_t f1;
    f2_t f2;

    template<typename... Args>
    auto invoke(std::true_type, std::false_type, Args&&... args) {
        return f1(std::forward<Args>(args)...);
    }

    template<typename... Args>
    auto invoke(std::false_type, std::true_type, Args&&... args) {
        return f2(std::forward<Args>(args)...);
    }
};


#include <iostream>
#include <cassert>

void f() {
    std::cout << "f()\n";
}
    
void f(int) {
    std::cout << "f(int)\n";
}

struct g {
    int operator()() {
        std::cout << "g()\n";
        return 0;
    }
    
    float operator()(int) {
        std::cout << "g(int)\n";
        return 1;
    }
};

int main(void)
{
    multifunction<void(), void(int)> mf{f, f};
    mf();
    mf(0);
    
    multifunction<int(), float(int)> mg{g{}};
    int i = mg();
    assert(i == 0);
    float f = mg(0);
    assert(f == 1);
}