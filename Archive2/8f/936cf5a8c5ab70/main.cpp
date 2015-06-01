#include <iostream>
#include <boost/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>

namespace mpl = boost::mpl;

struct meta_func
{
    template<typename T, typename U>
    struct apply : mpl::bool_< boost::is_same<T,U>::value
                               || boost::is_base_of<T,U>::value > {};
};

template<typename MetaFunc, typename TypeList, typename T>
void test()
{
    typedef typename mpl::transform<TypeList, typename MetaFunc::template apply<T, mpl::_1> >::type compatible_types;
    struct{} _ = compatible_types();
}

int main()
{
    test<meta_func, mpl::vector<int, char, int>, int>();
}
