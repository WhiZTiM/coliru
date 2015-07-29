#include <iostream>
#include <vector>
#include <array>
#include <memory>

    namespace easy_op {
      template<class Rhs>
      struct op_t {
        Rhs rhs;
      };
      constexpr static struct do_opt {
        template<class Rhs>
        constexpr op_t<Rhs> operator[](Rhs&& rhs)const{
          return {std::forward<Rhs>(rhs)};
        }
        constexpr do_opt() {}
      } const op;
      template<class Lhs, class Rhs>
      auto operator*( Lhs&& lhs, op_t<Rhs>&& rhs )
      -> decltype( (*std::declval<Lhs>())[std::declval<Rhs>()] )
      {
        return (*std::forward<Lhs>(lhs))[std::forward<Rhs>(rhs.rhs)];
      }
    }
    using easy_op::op;

    
int main() {
    std::unique_ptr< std::vector<int> > p = std::make_unique<std::vector<int>>();
    *p = {0,1,2,3,4,5};
    for(std::size_t i = 0; i < p->size(); ++i) {
        std::cout << p*op[i];
    }
    std::cout << '\n';
}