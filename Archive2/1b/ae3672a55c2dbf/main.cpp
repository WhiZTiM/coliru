#include <string>
#include <vector>
#include <iostream>
#include <utility>

    template<std::size_t n>
    using idx_t=std::integral_constant<std::size_t, n>;
    template<std::size_t n>
    idx_t<n> idx;

    constexpr int square( int x ) { return x*x; }
    constexpr int power( int base, size_t pow ) {
      return (pow==0)?1:
        (pow==1)?base:
          (
            square(power(base, pow/2))
              *( (pow%2)?base:1 )
          );
    }
    
    template<char... cs>
    struct helper:idx_t<0>{};
    template<char c0, char...cs>
    struct helper<c0, cs...>:idx_t< (c0-'0') * power(10, sizeof...(cs)) + helper<cs...>{} > {};
    
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
    f[17_idx];
    f[137_idx];
    f[1337_idx];
}
