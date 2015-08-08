#include <string>
#include <vector>
#include <iostream>
#include <utility>


    namespace named_operator {
      template<class D>struct make_operator{
        constexpr make_operator(){}
      };
      template<class T, char, class O> struct half_apply { T&& lhs; };

      template<class Lhs, class Op>
      constexpr
      half_apply<Lhs, '*', Op>
      operator*( Lhs&& lhs, make_operator<Op> ) {
        return {std::forward<Lhs>(lhs)};
      }

      template<class Lhs, class Op, class Rhs>
      constexpr auto
      times( Lhs&& lhs, Op, Rhs&& rhs, ... )
      -> decltype( invoke( std::declval<Lhs>(), Op{}, std::declval<Rhs>() ) )
      {
        return invoke( std::forward<Lhs>(lhs), Op{}, std::forward<Rhs>(rhs)     );
      }

      template<class Lhs, class Op, class Rhs>
      constexpr auto
      operator*( half_apply<Lhs, '*', Op>&& lhs, Rhs&& rhs )
      -> decltype(
        times( std::declval<Lhs>(), Op{}, std::declval<Rhs>() )
      )
      {
        return times( std::forward<Lhs>(lhs.lhs), Op{}, std::forward<Rhs>(rhs) );
      }
    }

    namespace power {
      template<typename T>
      constexpr T sqr(T a) {
        return a * a;
      }

      template<typename T>
      constexpr T power(T a, std::size_t n) {
        return (n == 0) ? 1 : sqr(power(a, n / 2)) * (n % 2 == 0 ?  1 : a);
      }

      namespace details {
        struct pow_tag {};
        constexpr named_operator::make_operator<pow_tag> pow;

        template<class Scalar>
        constexpr Scalar times( Scalar lhs, pow_tag, std::size_t rhs ) {
          return power( std::forward<Scalar>(lhs), rhs );
        }
      }
      using details::pow;
    }

    using power::pow;
    
    int array[ 2 *pow* 10 ] = {0};

int main()
{
    std::cout << sizeof(array)/sizeof(int) << "\n";
}
