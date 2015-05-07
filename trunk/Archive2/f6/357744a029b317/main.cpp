#include <iostream>

// enable_if
template <bool, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
    typedef T type;
};

// Map any type to void
template <class T>
struct type_to_void {
    typedef void type;
};

// trait that is true when T::return_type exists
template <class T, class Enable = void>
struct has_return_type_typedef {
    enum { value = false };
};

template <class T>
struct has_return_type_typedef<T, typename type_to_void<typename T::return_type>::type>
{
    enum { value = true };
};

// Base template
template <class Callable, class Enable = void>
struct return_type_info {
};

// Specialisation for functors with return_type typedef
template <class Callable>
struct return_type_info<Callable, typename enable_if<has_return_type_typedef<Callable>::value>::type> {
  typedef Callable function_type;
  typedef typename Callable::return_type return_type;
};

// Specialisation for functions
template <class ReturnType, class ArgumentType>
struct return_type_info<ReturnType(*)(ArgumentType)> {
    typedef ReturnType(*function_type)(ArgumentType);
    typedef ReturnType return_type;
};

// A function that uses the deduced type info...
template <class Callable>
typename return_type_info<Callable>::return_type call(Callable f, double x) {
    return f(x);
}

// ******** User code ********

double square(double x) {
    return x * x;
}

struct Square {
    typedef double return_type;
    
    double operator()(double x) {
        return x * x;
    }
};

struct Cube {
    double operator()(double x) {
        return x * x * x;
    }
};

int main() {
    // Plain function
    std::cout << call(square, 3.) << "\n";
    
    // Functor with typedef
    Square sq;
    std::cout << call(sq, 3.) << "\n";
    
    // Functor without typedef
    Cube c;
    std::cout << call(c, 3.) << "\n";
    
    return 0;
}
