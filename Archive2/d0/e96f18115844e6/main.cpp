#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>

    template<class Sig>
    struct ignore_extra_args_helper;
    template<class R, class...Args>
    struct ignore_extra_args_helper<R(Args...)> {
      template<class F>
      auto operator()( F&& f ) {
        return [f = std::forward<F>(f)](Args...args, auto&&...)->R{
          return f(std::forward<Args>(args)...);
        };
      }
    };
    template<class Sig, class F>
    auto ignore_extra_args( F&& f ) {
      return ignore_extra_args_helper<Sig>{}(std::forward<F>(f));
    }
    
    
    typedef std::function<void(int a, int b)> f1; 
    typedef std::function<void(int a)> f2; 

    std::vector<f1> m;

    template<class F, decltype(std::declval<F const&>()(1,1))* =nullptr>
    void add(F&& f) {
      m.push_back(std::forward<F>(f));
    }

    template<class F, class...Unused>
    void add(F&& f, Unused&&...) {
      add( ignore_extra_args<void(int)>(std::forward<F>(f)) );
    }

int main()
{
    auto f2 = ignore_extra_args<int(int)>([](int x){return x+3;});
    std::cout << f2(1,2,3) << '\n';
    add( [](int a, int b) { std::cout << a << ',' << b << '\n'; } );
    add( [](int a) { std::cout << a*1000 << '\n'; } );
    for (auto && f:m) {
        f(1,2);
    }
}
