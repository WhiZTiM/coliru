#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/find_if.hpp>
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

template<typename Begin, typename End>
struct has_vector_string_member
{
    using elem_type = typename boost::remove_reference<typename boost::remove_cv<typename boost::fusion::result_of::deref<Begin>::type>::type>::type;
    static constexpr bool result = boost::is_same<elem_type, std::vector<std::string>>::value ||
    has_vector_string_member<typename boost::fusion::result_of::next<Begin>::type, End>::result;
};

template<typename End>
struct has_vector_string_member<End, End>
{
    static constexpr bool result = false;
};

template<typename Sequence>
constexpr bool has_vector_member()
{
    return has_vector_string_member
    <
       typename boost::fusion::result_of::begin<Sequence>::type,
       typename boost::fusion::result_of::end<Sequence>::type
    >::result;
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