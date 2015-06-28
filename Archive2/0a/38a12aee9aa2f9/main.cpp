#define BOOST_PP_VARIADICS
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#define OP(s, state, x) state namespace x {
#define NS(...) BOOST_PP_SEQ_FOLD_LEFT(OP, , BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

NS(foo, bar, baz)

int x = 0;

// you probably need to define a macro for this as well 
}}}

int main() {
    foo::bar::baz::x = 42;
}