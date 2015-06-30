#include <cmath>
#include <iostream>

// enable_if, and related stuff

struct true_type {
  enum { value = true };
};

struct false_type {
  enum { value = false };
};

template <bool condition, typename T = void>
struct enable_if { };

template<typename T>
struct enable_if<true, T> {
  typedef T type;
};

// Traits

template <typename function_type>
struct is_f_x_reference : false_type {};

template <>
struct is_f_x_reference<double(double)> : true_type {};

template <typename function_type>
struct is_f_x_pointer : false_type {};

template <>
struct is_f_x_pointer<double(*)(double)> : true_type {};

template <typename function_type, typename enable = void>
struct is_f_x_functor : false_type {};

namespace is_f_x_functor_helper {

typedef char no_type;
typedef long yes_type;

template <typename T>
class checker {
    no_type do_check();
};

template<>
class checker<int> {
    no_type do_check();
};

template<>
class checker<double> {
    yes_type do_check();
};

template <typename T> checker<T> double_checker(const T& x);

} // namespace is_f_x_functor_helper

template <typename function_type>
struct is_f_x_functor<function_type,
    typename enable_if<
            sizeof(is_f_x_functor_helper::double_checker(function_type()(0.0)).do_check())
            == sizeof(is_f_x_functor_helper::yes_type)
        >::type
    >
 : true_type {};

// Function call traits

template <typename function_type, typename enable = void>
struct function_traits
{
    // Empty!
};

template <typename function_type>
struct function_traits<function_type,
    typename enable_if<is_f_x_reference<function_type>::value ||
                       is_f_x_pointer<function_type>::value ||
                       is_f_x_functor<function_type>::value
                      >::type
    > {
   static void call(const function_type& f, double x, double& fx) {
       fx = f(x);
   }
};

// Library function

template <class callable>
double library_function(const callable& f, double x) {
    return f(x);   
}

// User code

double function(double x) {
    return sin(x) / x;
}

struct functor {
    double operator()(double x) const { return sin(x) / x; }
};

double incompatible_function(int x) {
    return x*x + 0.5;
}

int another_incompatible_function(double x) {
    return static_cast<int>(x+0.5);
}

// Test

int main() {
    std::cout << library_function(function, 0.5) << "\n";
    std::cout << library_function(&function, 0.5) << "\n";
    std::cout << library_function(functor(), 0.5) << "\n";
    std::cout << library_function(another_incompatible_function, 3) << "\n"; // SHOULD FAIL
    return 0;
}
