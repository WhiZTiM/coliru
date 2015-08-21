template <class MathFunction> 
double foo (MathFunction function) {
    return function(1);
}

double test (double d) {
    return d;
}

struct functor {
    double operator () (double d) {
        return 2*d;
    }
};

int main () {
    foo(test);
    foo(functor{});
    foo([](double d){return d;});
}
