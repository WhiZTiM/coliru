#include <boost/fusion/adapted.hpp>
#include <boost/fusion/sequence/io/out.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/view.hpp>
#include <iostream>

namespace fuz = boost::fusion;

template <typename T, typename U>
class DoubleTemplate
{
};

namespace demo
{
    struct foos
    {
        DoubleTemplate<int, int> ro;
    };
}

BOOST_FUSION_ADAPT_STRUCT( demo::foos,
    (DoubleTemplate<int,int>, ro) )

int main()
{
    demo::foos f;
    f.ro = DoubleTemplate<int,int>();
 
}