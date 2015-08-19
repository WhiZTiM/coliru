#include <boost/fusion/adapted.hpp>
#include <boost/fusion/sequence/io/out.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/view.hpp>
#include <iostream>

template <typename T, typename U>
class DoubleTemplate
{
};

namespace demo
{
    struct adaptee
    {
        DoubleTemplate<int, int> dt;
    };
}

BOOST_FUSION_ADAPT_STRUCT( demo::adaptee,
    (DoubleTemplate<int, int>, dt) )

int main()
{
    demo::adaptee a;
    a.dt = DoubleTemplate<int, int>();
 
}