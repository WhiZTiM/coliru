#include <iostream>
#include <cmath>

namespace detail {    
    struct expand_impl final {        
        template <class Arg>
        constexpr inline 
            expand_impl(Arg&&) noexcept 
        {}
    };

    struct empty_pack final {};
            
    template <bool HasArgs = true>
    struct helper {
        typedef const detail::expand_impl expand_type[];
    };
    
    template <>
    struct helper<false> {
        typedef const detail::empty_pack expand_type;
    };
}

using expand = typename detail::helper<true>::expand_type;

template <typename... Args>
using expand_if = typename detail::helper<(sizeof...(Args) > 0)>::expand_type;

template <typename... Args>
constexpr inline bool empty(Args&&...) noexcept {
    return !sizeof...(Args);
}



template<typename... Args>
void printer(Args&&... args) {
    expand_if<Args...> {
        std::cout <<  args << '\n'...
    };
    
    if (empty(args...)) { 
        std::cout <<  "No args" << '\n';    
    }
}

template<typename... Args>
void square(Args&&... args) {
    expand_if<Args...> {
        std::cout << args*args << '\n'...
    };
}

template<typename... Args>
void abs(Args&&... args) {
    expand {
        std::cout << std::abs(args) << '\n'...,
        0
    };
}

template<typename... Args>
void printer_int(Args&&... args) {
    expand {
        std::cout << std::abs(args) << std::endl...,
        std::cout << "Printing once again all the numbers: " << std::endl,
        std::cout << "    Once again " << std::abs(args) << std::endl...,
        std::cout << "EOF Printing once again all the numbers." << std::endl
    };
}

template<typename... Args>
float sum(Args&&... args) {
    float res = 0;
    expand_if<Args...> {
        res += args...
    };
    
    return res;
}
template <class T> void foo(T&&) {}

template<typename... Args>
void void_res(Args&&... args) {
    expand_if<Args...> {
        (foo(args), 0)... // `void` return type
    };
}

int main() {
    printer(1, 2, 3, "abc");
    square(1, 2, 3, 15.1);
    abs(1, -12, 3, -15.1);
    abs();
    printer_int(1, 2, 3, 4, 5, 6, 7);
    printer_int();
    std::cout << sum(12, 13, 100, -83) << std::endl;
    void_res(1, 2, 3, 4, 5, 6, 7);
    printer();
}
