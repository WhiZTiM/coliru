#include <vector>
#include <utility>
#include <iterator>
#include <algorithm>
#include <iostream>

    template<class F, class R, class Out>
    struct convert_t {
      F f;
      R r;
      // TODO: upgrade std::begin calls with Koenig lookup
      template<class D>
      operator D()&&{
        D d;
        std::transform(
          std::begin(std::forward<R>(r)),
          std::end(std::forward<R>(r)),
          std::back_inserter(d),
          std::forward<F>(f)
        );
        return d;
      }
      template<template<class...>class Z, class Result=Z<
        typename std::decay<Out>::type
      >>
      Result to()&&{return std::move(*this);}
    };
    template<class F, class R,
        class dF=typename std::decay<F>::type,
        class dR=typename std::decay<R>::type,
        class R_T=decltype(*std::begin(std::declval<dR>())),
        class Out=typename std::result_of<dF&(R_T)>::type
    >
    convert_t<dF,dR,Out>
    convert( F&& f, R&& r ) { return {std::forward<F>(f), std::forward<R>(r)}; }

double Convert(int x){return x+0.5;}
int main() {
    std::vector<int> vec{1,2,3};
    auto r = convert(Convert, vec).to<std::vector>();
    for (auto&& x:r)
        std::cout << x << '\n';
    std::vector<double> r2 = convert(Convert, vec);
    for (auto&& x:r)
        std::cout << x << '\n';
}
