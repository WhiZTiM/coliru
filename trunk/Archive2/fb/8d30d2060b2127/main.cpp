#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>

template<class F>
struct recursive_t {
  F f;

  // note Self must be an lvalue reference.  Things get
  // strange if it is an rvalue:
  // invoke makes recursive ADL work a touch better.
  template<class Self, class...Args>
  friend auto invoke( Self& self, Args&&...args )
  -> decltype( self.f( std::declval<Self&>(), std::declval<Args>()... ) )
  {
    return self.f( self, std::forward<Args>(args)... );
  }
  // calculate return type using `invoke` above:
  template<class Self, class...Args>
  using R = decltype( invoke( std::declval<Self>(), std::declval<Args>()... ) );

  template<class...Args>
  R<recursive_t&, Args...> operator()(Args&&...args)
  {
    return invoke( *this, std::forward<Args>(args)... );
  }
  template<class...Args>
  R<recursive_t const&, Args...> operator()(Args&&...args)const
  {
    return invoke( *this, std::forward<Args>(args)... );
  }
};

template<class F>
recursive_t< std::decay_t<F> > recurse( F&& f )
{
  return {std::forward<F>(f)};
}

int main() {
    auto fib = recurse( [](auto&& fib, int x){
        if (x<2) return 1;
        return fib(x-1)+fib(x-2);
    } );
    for (int i = 0; i < 10; ++i)
        std::cout << fib(i) << '\n';
}