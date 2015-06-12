#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/equal_to.hpp>

namespace mpl = boost::mpl;

typedef mpl::vector_c<int, 1, 1, 1> vec1;
typedef mpl::vector_c<int, 2, 2, 2> vec2;
typedef mpl::vector_c<int, 3, 3, 3> vec3;
typedef mpl::vector<vec1, vec2, vec3> vvec;

typedef typename mpl::lambda<
        mpl::fold<
            mpl::_1, 
            mpl::int_<0>, 
            typename mpl::lambda<mpl::plus<mpl::_1, mpl::_2> >::type
        >
    >::type lam;

typedef typename mpl::fold<
        vvec, 
        mpl::int_<0>, 
        mpl::plus<mpl::_1, mpl::protect<lam>::type::apply<mpl::_2> >
    >::type result;

static_assert(mpl::equal_to<result, mpl::int_<18>>::value, "should be 18");

int main() {}
