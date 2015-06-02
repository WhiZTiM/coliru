#include <iostream>
#include <functional>
#include <vector>
#include <boost/optional.hpp>

template<typename T>
struct val
{
    val(T val) : value{val} {}
    
    T value;
};

template<>
struct val<void> { val() {} };

template<typename F, typename G>
constexpr auto composite(F&& f, G&& g) {
    return [f, g](auto&&... xs) -> decltype(auto) {
        return g(f(xs...));        
    };    
}

template<typename> struct continuation;

template<typename F>
constexpr auto make_continuation(F&& func) {
    return continuation<F>(std::forward<F>(func));
}

namespace detail {
template<typename F, typename Enable, typename... As>
struct invoke_impl;

template<typename F, typename... As>
struct invoke_impl<F, typename std::enable_if<std::is_void<typename std::result_of<F(As...)>::type>::value>::type, As...> {
    constexpr auto operator()(const F& f, As&&... args) const {
        f(std::forward<As>(args)...);
        return val<void>{};
    }
};

template<typename F, typename... As>
struct invoke_impl<F, typename std::enable_if<!std::is_void<typename std::result_of<F(As...)>::type>::value>::type, As...> {
    constexpr auto operator()(const F& f, As&&... args) const {
        return val<decltype(f(std::forward<As>(args)...))>{f(std::forward<As>(args)...)};
    }
};
} // detail

template<typename F, typename... As>
using invoke = detail::invoke_impl<F, void, As...>;

template<typename F>
struct continuation {
   constexpr continuation(F&& f) : f{std::forward<F>(f)} {}
   
   template<typename... As>
   constexpr auto operator()(As&&... args) const {
        return invoke<F, As...>{}(f, std::forward<As>(args)...);
   }
   
   template<typename G>
   constexpr auto then(G&& g) && {
       return make_continuation(composite(*this, g));
   }
   
   F f;
};

int main(int argc, char* argv[]) {
    auto cont = make_continuation([](auto val) { 
                        return val; 
                    })
                    .then([](auto val) { 
                        return val.value; 
                    })
                    .then([](auto val) { 
                        std::cout << val.value; 
                    })
                    .then([](auto) {
                        std::cout << std::endl;    
                    });
    cont(1);
    
    return 0;   
}
