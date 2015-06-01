#include <iostream>
#include <boost/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>

namespace mpl = boost::mpl;

template<typename T, typename U>
struct meta_func : mpl::bool_< boost::is_same<T,U>::value
                               || boost::is_base_of<T,U>::value >
{
};

template<typename TypeList, typename T>
void test()
{
    typedef typename mpl::transform<TypeList, meta_func<T, mpl::_1> >::type compatible_types;
    struct{} _ = compatible_types();
}

int main()
{
    test<mpl::vector<int, char, int>, int>();
}
