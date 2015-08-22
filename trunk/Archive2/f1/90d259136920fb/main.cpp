#include <iostream>
#include <string>
#include <vector>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/fusion/include/define_struct.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/cat.hpp>

template <int N>
struct S
{
    char data[N];  
};

struct My1
{
    char a[3];
    char aa[7];
    char aaa[15];
    char aaaa[4];
};

struct My2
{
    S<3> a;
    S<7> aa;
    S<15> aaa;
    S<4> aaaa;
};

struct MyStruct
{
    int x;
    int y;
};

#define GO(r, data, elem) elem
#define SEQ1        \
    ((int,x))       \
    ((int,y))

BOOST_FUSION_DEFINE_STRUCT( 
    (),
    MyStruct1,
    BOOST_PP_SEQ_FOR_EACH(GO, ,SEQ1)      
    )

#define PRINT(unused, number, data) \
    std::cout << number << std::endl;

 
int main()
{
    MyStruct1 a;
    a.x = 1;
    a.y = 2;
    BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(SEQ1), PRINT, "data")
    
    std::cout << sizeof(My1) << std::endl;
    std::cout << sizeof(My2) << std::endl;
    
    
    
}
