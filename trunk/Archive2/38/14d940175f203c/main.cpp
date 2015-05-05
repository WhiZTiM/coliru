#include <iostream>

template <typename Callable>
struct function_traits {
    typedef typename Callable::return_type return_type;
    typedef typename Callable::argument_type argument_type;
    typedef Callable callable_type;
    
    static return_type call(callable_type f, argument_type x) {
        return f(x);
    }    
};

template <typename Ret, typename Arg>
struct function_traits<Ret(*)(Arg)> {
    typedef Ret return_type;
    typedef Arg argument_type;
    typedef Ret(*callable_type)(Arg);
    
    static return_type call(callable_type f, argument_type x) {
        return f(x);
    }
};

double square(const double& x) {
    return x * x;
}

struct Square {
    typedef double argument_type;
    typedef double return_type;
    
    double operator()(const double& x) {
        return x*x;
    }
};

template <typename Callable, typename ArgType>
typename function_traits<Callable>::return_type call(Callable f, ArgType x) {
    return f(x);
}

template <typename Callable, typename Ret, typename Arg>
struct member_function_wrapper {
    typedef Ret return_type;
    typedef Arg argument_type;
    Callable function;
    
    member_function_wrapper(Callable f) : function(f) {}
    
    return_type operator()(argument_type x) {
        return function(x);
    }
};

template <class Callable, class Ret, class Arg>
member_function_wrapper<Callable, Ret, Arg> wrap(Ret(Callable::*f)(Arg), Callable c) {
    return member_function_wrapper<Callable, Ret, Arg>(c);
}

struct Cube {
    double operator()(double x) {
        return x * x * x;
    }
};

int main() {
    std::cout << call(square, 2.) << "\n";
    Square sq;
    std::cout << call(sq, 2.) << "\n";
    Cube cb;
    std::cout << call(wrap(&Cube::operator(), cb), 2.) << "\n";
    return 0;
}
