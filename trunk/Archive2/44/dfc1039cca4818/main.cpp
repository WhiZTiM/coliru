#include <iostream>
#include <vector>
#include <set>
#if __cplusplus > 199711L
#include <array>
#endif
#include <boost/spirit/home/support/container.hpp>

#define DEFINE_HAS_SIGNATURE(traitsName, funcName, signature)                \
    template <typename U>                                                    \
    class traitsName                                                         \
    {                                                                        \
    private:                                                                 \
        typedef boost::uint8_t yes; typedef boost::uint16_t no;              \
        template<typename T, T> struct helper;                               \
        template<typename T> static yes check(helper<signature, &funcName>*);\
        template<typename T> static no check(...);                           \
    public:                                                                  \
        static const bool value = sizeof check<U>(0) == sizeof(yes);         \
    }

#if __cplusplus > 199711L
DEFINE_HAS_SIGNATURE(has_resize, T::resize, void (T::*)(typename T::size_type));
#else
DEFINE_HAS_SIGNATURE(has_resize, T::resize, void (T::*)(typename T::size_type, typename T::value_type));
#endif

class xstream { }; // For this example, the class doesn't need to do anything.

template <typename T>
typename boost::enable_if_c<
    !boost::spirit::traits::is_container<T>::value,
    xstream &>::type
    operator>>(xstream &ibs, T &b)
{
    std::cout << "non-container type" << std::endl;
    return ibs;
}

template <typename C>
typename boost::enable_if_c<
    boost::spirit::traits::is_container<C>::value && has_resize<C>::value,
    xstream &
>::type
operator>>(xstream &ibs, C &c)
{
    std::cout << "variable-length container type" << std::endl;
    ibs >> *c.begin();
    return ibs;
}

template <typename C>
typename boost::enable_if_c<
    boost::spirit::traits::is_container<C>::value && !has_resize<C>::value,
    xstream &
>::type
operator>>(xstream &ibs, C &c)
{
    std::cout << "fixed-length container type" << std::endl;
    ibs >> *c.begin();
    return ibs;
}

int main()
{
    int i;
    std::vector<int> vi;
    std::set<int> si;
#if __cplusplus > 199711L
    std::array<int, 1> ai;
#endif
    xstream xs;
    xs >> i >> vi >> si;
#if __cplusplus > 199711L
    xs >> ai;
#endif
}
