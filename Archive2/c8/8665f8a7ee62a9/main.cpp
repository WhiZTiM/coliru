#include <boost/mpl/vector.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>

#include <boost/mpl/bool.hpp>


#define IS_TAG_TRAITS(name)                                               \
    template <typename T, typename = void>                                      \
    struct Is##name : public boost::mpl::false_ {};                             \
                                                                                \
    template <typename T>                                                       \
    struct Is##name<T, typename T::Is##name> : public boost::mpl::true_ {};

#define AGG0X_IS_TAG(name, type) Tag::Is##name<type>


#define DEFINE_TAG(name)                                                     \
    struct name {typedef void Is##name;};                                       \
    IS_TAG_TRAITS(name)




namespace Tag {
    
DEFINE_TAG(BoundingBoxPolicy)
DEFINE_TAG(ConversionDir)
    
}



struct Void;

namespace BoundingBoxPolicy {

struct Last : public Tag::BoundingBoxPolicy {};
struct All : public Tag::BoundingBoxPolicy {};
    
}

namespace ConversionDir {

struct Direct : public Tag::ConversionDir {};
struct Inverse : public Tag::ConversionDir {};

}


#if 1

template <typename Default, typename Predicate, typename A0, typename A1, bool B0 = boost::mpl::apply<Predicate, A0>::type::value, bool B1 = boost::mpl::apply<Predicate, A1>::type::value>
struct Index { typedef Default type; };

template <typename Default, typename Predicate, typename A0, typename A1, bool B1>
struct Index<Default, Predicate, A0, A1, true, B1> { typedef A0 type; };

template <typename Default, typename Predicate, typename A0, typename A1>
struct Index<Default, Predicate, A0, A1, false, true> { typedef A1 type; };


#else


#define TPL_TYPE_x_(n)                  BOOST_PP_ENUM_PARAMS(n, typename A)

#define TPL_A_x_(n)                     BOOST_PP_ENUM_PARAMS(n, A)

#define TPL_BOOL_DEF(z, n, data)        bool B ## n = boost::mpl::apply<Predicate, A ## n>::type::value
#define TPL_BOOL_x_(n)                  BOOST_PP_ENUM(n, TPL_BOOL_DEF, ~)

#define TPL_BOOL(z, n, init_num)        bool BOOST_PP_CAT(bool B, BOOST_PP_ADD(init_num, n))
#define TPL_BOOL_RANGE(from, to)        BOOST_PP_ENUM(BOOST_PP_SUB(to, from), TPL_BOOL, from)

#define TPL_FALSE(z, n, data)           false
#define TPL_FALSE_x_(n)                 BOOST_PP_ENUM_TRAILING(


#define INDEX_SPEC(z, num_B, num_A) \
    template <typename Default, typename Predicate, TPL_PARAM_x_(num_A), TPL_BOOL_RANGE(BOOST_PP_SUB(num_A, num_B), num_A)> \
    struct Index<Default, Predicate, TPL_A_x_(num_A), true, B1> { typedef BOOST_PP_CAT(A, BOOST_PP_SUB(num_A, num_B)) type; };


#define INDEX(z, n, data)                                                               \
    template <typename Default, typename Predicate, TPL_TYPE_x_(n), TPL_BOOL_x_(n)>     \
    struct Index { typedef Default type; };                                             \
                                                                                        \
    BOOST_PP_REPEAT(n, INDEX_SPEC, n)
    

BOOST_PP_REPEAT(10, INDEX, ~)

#endif


#define GET_OR_DEFAULT(Tag, Default)                                                                                        \
    typedef typename Index<Default, AGG0X_IS_TAG(Tag, boost::mpl::_), A0, A1>::type Tag;
    
    
template <typename A0 = Void, typename A1 = Void>
struct ColorFormat {
    GET_OR_DEFAULT(BoundingBoxPolicy, ::BoundingBoxPolicy::Last)
    GET_OR_DEFAULT(ConversionDir, ::ConversionDir::Direct)    
};



#include <iostream>

int main() {
    {
        typedef ColorFormat<BoundingBoxPolicy::All, ConversionDir::Inverse> ColorFormat;
        std::cout << boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::All>::value;
        std::cout << boost::is_same<ColorFormat::ConversionDir, ConversionDir::Inverse>::value;
    }
    {
        typedef ColorFormat<ConversionDir::Inverse, BoundingBoxPolicy::All> ColorFormat;
        std::cout << boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::All>::value;
        std::cout << boost::is_same<ColorFormat::ConversionDir, ConversionDir::Inverse>::value;
    }
    {
        typedef ColorFormat<ConversionDir::Inverse> ColorFormat;
        std::cout << boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::Last>::value;
        std::cout << boost::is_same<ColorFormat::ConversionDir, ConversionDir::Inverse>::value;
    }
    {
        typedef ColorFormat<> ColorFormat;
        std::cout << boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::Last>::value;
        std::cout << boost::is_same<ColorFormat::ConversionDir, ConversionDir::Direct>::value;
    }
    {
        typedef ColorFormat<> ColorFormat;
        std::cout << !boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::All>::value;
        std::cout << !boost::is_same<ColorFormat::ConversionDir, ConversionDir::Inverse>::value;
    }
    {
        typedef ColorFormat<ConversionDir::Inverse, ConversionDir::Direct> ColorFormat;
        std::cout << boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::Last>::value;
        std::cout << boost::is_same<ColorFormat::ConversionDir, ConversionDir::Inverse>::value;
    }
}