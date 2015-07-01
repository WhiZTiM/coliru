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

template <class T>
struct void_ {
    typedef void type;
};

template <class function_type, class enable = void>
struct has_return_type { enum { value = false }; };

template <class function_type>
struct has_return_type<function_type, typename void_<typename function_type::return_type>::type> {
    enum { value = true };
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
                   is_functor_with_signature<function_type, double(function_type::*)(double)>::value
                   >::type> { 
    static void call(function_type f, double x, double& fx) {
        std::cout << "specialisation: ";
        fx = f(x);
    }
};

template <class function_type>
struct call_traits<function_type, typename enable_if<has_return_type<function_type>::value>::type> {
    static void call(function_type f, double x, double& fx) {
        std::cout << "specialisation2: ";
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

struct functor1 {
    typedef double return_type;
    double operator()(double x) {
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
    // invalid functors
    foo(invalid_functor(), 0.5);
    return 0;
}
