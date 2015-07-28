#include <cstdio>
#include <boost/preprocessor.hpp>

#define PP_VARIADIC_ELEM(index, ...) BOOST_PP_IF(BOOST_PP_LESS(index, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), BOOST_PP_VARIADIC_ELEM(index, __VA_ARGS__), _Pragma("GCC error \"out of range\""))
 
int main() 
{
    std::printf("%d\n", PP_VARIADIC_ELEM(1, 1, 2, 3));
}