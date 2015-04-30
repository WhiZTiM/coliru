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
    
    template<class T0, class...Ts>
    using vector_t = std::vector<
      typename std::conditional<
        std::is_same<T0, void>::value,
        typename std::decay<first_t<Ts...>>::type,
        T0
      >::type
    >;
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
    template<class T>
    std::vector<T> make_vector() {
      return {};
    }
    
int main(int argc, const char * argv[]) {
    std::unique_ptr<test1> us(new test1());
    std::vector<std::unique_ptr<test1>> vec = make_vector( std::move(us) );
    auto v2 = make_vector<std::unique_ptr<int>>();
    auto v3 = make_vector<std::unique_ptr<int>>(std::make_unique<int>(3));
    return 0;
}