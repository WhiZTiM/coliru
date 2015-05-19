#include <boost/mpl/assert.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector.hpp>

using namespace boost;

struct T0;
struct T1;
struct T2;
struct T3;

typedef mpl::vector<T0, T1> s0;
typedef mpl::vector<T2, T3> s1;
typedef mpl::copy<
    s1,
    mpl::back_inserter<s0>
>::type concatenated;

int main()
{
    BOOST_MPL_ASSERT((
        mpl::equal<
            concatenated,
            mpl::vector<T0, T1, T2, T3>
        >
    ));
}
