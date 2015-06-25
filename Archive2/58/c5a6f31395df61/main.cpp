#include <iostream>
#include <boost/spirit/home/support/container.hpp>

#define DEFINE_HAS_SIGNATURE(traitsName, funcName, signature)               \
    template <typename U>                                                   \
    class traitsName                                                        \
    {                                                                       \
    private:                                                                \
        template<typename T, T> struct helper;                              \
        template<typename T>                                                \
        static char check(helper<signature, &funcName>*);                   \
        template<typename T> static int check(...);                         \
    public:                                                                 \
        static                                                              \
        const bool value = sizeof(check<U>(0)) == sizeof(char);             \
    }

DEFINE_HAS_SIGNATURE(has_resize, T::foo, int (T::*));

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
    xstream is;
    is >> i;
}
