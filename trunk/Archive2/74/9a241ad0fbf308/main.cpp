#include <iostream>
#include <memory>
#include <utility>
#include <vector>
class test1{
public:
    test1(){};
    test1(test1&&)=default;
};

    template<class...Ts>
    struct first {};
    template<class T, class...Ts>
    struct first<T,Ts...>{
      using type=T;
    };
    template<class...Ts>
    using first_t=typename first<Ts...>::type;
    
    template<class T>struct tag{using type=T;};
    template<class T, size_t n>struct get_tag:get_tag<typename T::type, n-1>{};
    template<class T>struct get_tag<T,0>:tag<T>{};
    
    template<class Tag, size_t n=1>using type_t=typename get_tag<Tag,n>::type;
    
    // build the return type:
    template<class T0, class...Ts>
    using vector_T = 
      type_t<std::conditional<
        std::is_same<T0, void>::value,
        first<typename std::decay<Ts>::type...>,
        tag<T0>
      >,2>;
    template<class T0, class...Ts>
    using vector_t = std::vector< vector_T<T0, Ts...> >;

    template<class T0=void, class...Ts, class R=vector_t<T0, Ts...>>
    R make_vector( Ts&&...ts ) {
      R retval;
      retval.reserve(sizeof...(Ts));
      using discard = int[];
      (void)discard{0,((
        retval.emplace_back( std::forward<Ts>(ts) )
      ),void(),0)...};
      return retval;
    }
    
template<class...Ts>
struct make_vec_later {
  std::tuple<Ts...> args; // could make this `Ts&&...`, but that is scary

   // make this && in C++14
  template<class T, size_t...Is>
  std::vector<T> get(std::index_sequence<Is...>) {
    return make_vector<T>(std::get<Is>(std::move(args))...);
  }

  // make this && in C++14
  template<class T>
  operator std::vector<T>(){
    return std::move(*this).template get<T>( std::index_sequence_for<Ts...>{} );
  }
};
template<class...Ts>
make_vec_later<Ts...> v(Ts&&...ts) {
  return {std::tuple<Ts...>(std::forward<Ts>(ts)...)};
}
    
int main(int argc, const char * argv[]) {
    std::unique_ptr<test1> us(new test1());
    std::vector<std::unique_ptr<test1>> vec = make_vector( std::move(us) );
    auto v2 = make_vector<std::unique_ptr<int>>();
    auto v3 = make_vector<std::unique_ptr<int>>(std::make_unique<int>(3));
    std::vector<int> v4 = v();
    std::vector<int> v5 = v(1,2,3,4.5);
    std::vector<std::vector<int>> v6 = v( v(1,2), v(3), v(4,5,6) );
    return 0;
}