#include <string>
#include <vector>
#include <iostream>
#include <utility>

    template<std::size_t n>
    using idx_t=std::integral_constant<std::size_t, n>;
    template<std::size_t n>
    idx_t<n> idx;
    
    template<char... cs>
    struct helper:idx_t<0>{};
    template<char c0>
    struct helper<c0>:idx_t< (c0-'0') > {};
    template<char c0, char...cs>
    struct helper<c0, cs...>:idx_t< (c0-'0') * 10 + helper<cs...>{} > {};
    
    template<char...cs>
    constexpr idx_t< helper<cs...>{} > operator""_idx() { return {}; }

    struct foo {
      template<std::size_t n>
      void operator[](idx_t<n>) const {
        char arr[n];
        std::cout << sizeof(arr) << '\n';
      }
    };


int main()
{
    foo f;
    f[idx_t<1>{}];
    f[idx<2>];
    f[3_idx];
}
