#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <vector>

    template<size_t N>
    using size=std::integral_constant<size_t, N>;

    template<
      class T, template<class...>class Operation,
      class Sig=std::result_of_t<Operation<size<0>>(std::vector<T> const&)>()
    >
    struct eraser;

    template<class T, template<class...>class Operation, class R, class...Args>
    struct eraser<T,Operation, R(Args...)> {
      std::vector<T> data;
      R(*f)(eraser const*, Args&&...);
      R operator()(Args...args)const{
        return f(this, std::forward<Args>(args)...);
      }
      template<size_t N>
      eraser( std::initializer_list<T> il, size<N> ):
        eraser( il.begin(), size<N>{} )
      {}
      template<size_t N>
      eraser( T const* ptr, size<N> ):
        data(ptr, ptr+N),
        f([](eraser const*self, Args&&...args)->R{
          return Operation<size<N>>{}(self->data, std::forward<Args>(args)...);
        })
      {}
    };
    template<class T, size_t ... Is>
    void some_func( std::vector<T> const&, std::index_sequence<Is...>) {
      std::cout << "called!\n";
    }
    template<class N>
    struct call_some_func {
      template<class T>
      void operator()(std::vector<T> const& v) const {
        some_func( v, std::make_index_sequence<N{}>{} );
      }
    };


    int main() {
      using A = eraser<std::string, call_some_func>;
      // List of variable length const arrays and their sizes
      std::vector<A> myAList {
        A({ std::string("String1"), std::string("String2") }, size<2>{}),
        A({ std::string("String1") }, size<1>{})
      };

      // How would I go about using the size of each array in a constexpr?
      for (auto const& a : myAList) {
        a();
      }
    }