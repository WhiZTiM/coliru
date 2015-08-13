#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/find.hpp>
#include <boost/fusion/include/end.hpp>

struct Obj1
{
    int value_1;
    std::string value_2;
};

BOOST_FUSION_ADAPT_STRUCT(
    Obj1,
    (int, value_1)
    (std::string, value_2)
)
 
struct Obj2
{
    int value_1;
    std::vector< std::string > names;
};

BOOST_FUSION_ADAPT_STRUCT(
    Obj2,
    (int, value_1)
    (std::vector<std::string>, names)
)

template<typename Sequence>
constexpr bool has_vector_member()
{
    return !boost::is_same
    <
       typename boost::fusion::result_of::find<Sequence, std::vector<std::string>>::type,
       typename boost::fusion::result_of::end<Sequence>::type
    >::value;
}

template < typename T >
class Foo
{
public:
    Foo() = default;
    template<typename Q = T>
    typename std::enable_if<has_vector_member<Q>(), void>::type func()
    {
        // Если у T есть поле типа std::vector< std::string > выполнить какие-то действия
        // Если его нет, то ничего не делать.
        std::cout << "has vector member" << std::endl;
    }
    
    template<typename Q = T>
    typename std::enable_if<!has_vector_member<Q>(), void>::type func()
    {
    }
};

int main()
{
    Foo<Obj2> o;
    o.func();
    Foo<Obj1> oo;
    oo.func();
}