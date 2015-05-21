#include <functional>
#include <utility>

template<typename...> struct void_t_impl { using type = void; };
template<typename... Ts> using void_t = typename void_t_impl<Ts...>::type;
template<typename Signature, typename = void> struct is_invokable : std::false_type {};
template<typename F, typename... Args> struct is_invokable<F(Args...), void_t<decltype(std::declval<F>()(std::declval<Args>()...))>> : std::true_type  {};

template<typename Sig1, typename Sig2>
class multifunction {
    using f1_t = std::function<Sig1>;
    using f2_t = std::function<Sig2>;

public:
    template<typename F>
    multifunction(F&& f) : f1{std::forward<F>(f)}, f2{std::forward<F>(f)} {};

    template<typename... Args>
    auto operator()(Args&&... args) {
        invoke(is_invokable<f1_t(Args...)>{}, is_invokable<f2_t(Args...)>{}, std::forward<Args>(args)...);
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

struct f {
    void operator()() {
        std::cout << "f()\n";
    }
    
    void operator()(int) {
        std::cout << "f(int)\n";
    }
};

int main(void)
{
    multifunction<void(), void(int)> mf{f{}};
    mf();
    mf(0);
}