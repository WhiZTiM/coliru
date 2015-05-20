#include <iostream>
#include <string>
#include <vector>

template<typename ...>
struct tuple_t;

template<typename X>
struct tuple_t<X>
{
    X value;
    
    template<typename V>
    tuple_t<X>( V && v ) 
    : value( std::forward<X>(v) )
    {}
};

template<typename X, typename ... Xs>
struct tuple_t<X, Xs...> : tuple_t<Xs...>
{
    using that = tuple_t<X, Xs...>;
    using base = tuple_t<Xs...>;
    const static size_t index = sizeof ... (Xs);

    X value;
    
    template<typename V, typename ... Vs>
    tuple_t<X, Xs...>( V && v, Vs && ... vs ) 
    : base( std::forward<Vs>(vs)... )
    , value( std::forward<X>(v) )
    {}
    
};

int main()
{
  tuple_t<int, double, size_t> t  {11, 13.3, 77};
  std::cout << ( t.tuple_t<size_t>::value ) << "\n";
  
}
