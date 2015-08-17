#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <sstream>
#include <type_traits>
#include <memory>

template <typename Result, typename... Parameters>
class Superposable {
  public:
    virtual void operator()(Result& result, const Parameters&...) const = 0;
};


class MyField : public Superposable<double, double, double> {
  public:
    void operator()(double& result, const double& p1, const double& p2) const {
      result = p1 + p2;
    }
};

template<class...>struct types{using type=types;};

template<template<class...>class Z, class...Args>
constexpr types<Args...> extract_args( Z<Args...> const& ) { return {}; }

template<template<class...>class Z, class T>
using extract_args_from = decltype( extract_args<Z>( std::declval<T>() ) );

template<class S, class Args=extract_args_from<Superposable, S>>
class Superposition;

template<class S, class Result, class...Parameters>
class Superposition< S, types<Result, Parameters...>> {
  private:
    std::vector< std::shared_ptr<S> > elements;
  public:

     // This is the problem. How do I do this?
    void operator()(Result& result, const Parameters&... parameters) const {
       for(auto p : elements){
          Result r;
          p->operator()(r, parameters...);
          result += r;
       }
    }
};

Superposition< MyField > test;

int main() {
    double d;
    test(d, 1.0, 2.0);
//    test(d, 1.0, 2.0, 3.0); // <- does not compile
}