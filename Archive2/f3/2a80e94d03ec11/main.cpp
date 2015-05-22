#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/to_tuple.hpp>

#define _AUTO(_0, _1, name) \
    (auto&& name)

#define _BODY(...) \
    { return __VA_ARGS__; }

#define LR(...) \
    BOOST_PP_SEQ_TO_TUPLE(BOOST_PP_SEQ_FOR_EACH(_AUTO, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))) _BODY

#include <iostream>

int main()
{
    std::cout << []LR(x)(x)("test");                                                                                                   
    std::cout << []LR(x, y)(x + y)(2, 3);                                                                                              
    std::cout << []LR(x, y)(x + y)(std::string("hello "), std::string(" world!"));                                                          
}