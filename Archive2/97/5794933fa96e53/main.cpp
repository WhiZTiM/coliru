#include <cmath>
#include <iostream>
#include <string>

// enable_if...
template <bool condition, typename T = void>
struct enable_if { };

template<typename T>
struct enable_if<true, T> {
  typedef T type;
};

// type traits...

template <class function_type, class signature>
struct is_functor_with_signature {
  typedef char (& yes)[1];
  typedef char (& no)[2];
  
  template <class T, T> struct check;
  
  template <class T> static yes deduce(check<signature, &T::operator()> *);
  template <class> static no deduce(...);
  
  enum {
      value = sizeof(deduce<function_type>(0)) == sizeof(yes)
  };
};

// call traits

template <class function_type, class enable = void>
struct call_traits {
    static void call(const function_type& f, double x, double& fx) {
        std::cout << "base template: ";
    }
};

template <class function_type>
struct call_traits<function_type, typename enable_if<
                   is_functor_with_signature<function_type, double(function_type::*)(double)>::value ||
                   is_functor_with_signature<function_type, double(function_type::*)(double) const>::value ||
                   is_functor_with_signature<function_type, double(function_type::*)(const double)>::value ||
                   is_functor_with_signature<function_type, double(function_type::*)(const double) const>::value ||
                   is_functor_with_signature<function_type, double(function_type::*)(const double&)>::value ||
                   is_functor_with_signature<function_type, double(function_type::*)(const double&) const>::value
                   >::type> { 
    static void call(function_type f, double x, double& fx) {
        std::cout << "specialisation: ";
        fx = f(x);
    }
};

// functions
template <class function_type>
void foo(function_type f, double x) {
    double fx = 0.;
    call_traits<function_type>::call(f, x, fx);
    std::cout <<  fx << "\n";
}

// test

double func1(double x) {
    return sin(x) / x;
}

struct invalid_functor {
    int operator()(double x) const {
        return 1 + static_cast<int>(x);
    }
};

struct invalid_functor_2 {
    double operator()(int x) const {
        return x + 0.5;
    }
};

struct invalid_functor_3 {
    double operator()(const std::string& x) const {
        static_cast<void>(x);
        return 3;
    }
};

struct functor1 {
    double operator()(double x) {
        return sin(x) / x;
    }
};

struct functor2 {
    double operator()(double x) const {
        return sin(x) / x;
    }
};

struct functor3 {
    double operator()(const double x) {
        return sin(x) / x;
    }
};

struct functor4 {
    double operator()(const double x) const {
        return sin(x) / x;
    }
};

struct functor5 {
    double operator()(const double& x) {
        return sin(x) / x;
    }
};

struct functor6 {
    double operator()(const double& x) const {
        return sin(x) / x;
    }
};

int main() {
    // function
    foo(func1, 0.5);
    
    // function pointer
    foo(&func1, 0.5);
    
    // valid functors
    foo(functor1(), 0.5);
    foo(functor2(), 0.5);
    foo(functor3(), 0.5);
    foo(functor4(), 0.5);
    foo(functor5(), 0.5);
    foo(functor6(), 0.5);
    // invalid functors
    foo(invalid_functor(), 0.5);
    foo(invalid_functor_2(), 0.5);
    foo(invalid_functor_3(), 0.5);
    return 0;
}
