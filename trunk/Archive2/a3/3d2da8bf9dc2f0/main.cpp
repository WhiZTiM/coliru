#include <cmath>
#include <iostream>

// Library code - helper stuff

struct true_type {
    enum { value = true };
};

struct false_type {
    enum { value = false };
};

template <bool Condition, typename T = void>
struct enable_if {
};

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};

// Library code - function traits

template <class function_type, class enable = void>
struct is_simple_functor : false_type {};

template <class function_type>
struct is_simple_functor<function_type,
                         typename enable_if<
                             sizeof(function_type()(0.0)) == sizeof(double)
                         >::type> : true_type {};

template <typename function_type, typename enable = void>
struct function_traits {
    // nothing here
};

template <>
struct function_traits<double(double)> {
    static void call(double(*f)(double), double x, double& fx) {
        std::cerr << "double(double) specialisation: ";
        fx = f(x);
    }
};

template <>
struct function_traits<double(*)(double)> {
    static void call(double(*f)(double), double x, double& fx) {
        std::cerr << "double(*)(double) specialisation: ";
        fx = f(x);
    }
};

template <class function_type>
struct function_traits<function_type, typename enable_if<is_simple_functor<function_type>::value>::type> {
    static void call(const function_type& f, double x, double& fx) {
        std::cerr << "is_simple_functor specialisation: ";
        fx = f(x);
    }
};

// Library code - user-callable function

template <class function_type>
double library_func(const function_type& f, double x) {
    double fx = 0.0;
    function_traits<function_type>::call(f, x, fx);
    return fx;
}

// User code

double function(double x) { return sin(x) / x; }

struct functor {
    double operator()(double x) const { return sin(x) / x; }
};

// Test
int main() {
    std::cout << library_func(function, 0.5) << "\n";
    std::cout << library_func(&function, 0.5) << "\n";
    std::cout << library_func(functor(), 0.5) << "\n";
    return 0;
}