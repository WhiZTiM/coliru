#include <boost/mpl/assert.hpp>

BOOST_MPL_ASSERT_MSG(true, SOME_MESSAGE, ()); // does nothing
BOOST_MPL_ASSERT_MSG(false, SOME_MESSAGE, ()); // prints an error mentionning SOME_MESSAGE