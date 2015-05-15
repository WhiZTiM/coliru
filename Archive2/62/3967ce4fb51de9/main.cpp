#include <boost/mpl/vector.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>

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


#define GET_OR_DEFAULT(Tag, Default)                                                                                        \
    typedef typename boost::mpl::find_if<Parameters, AGG0X_IS_TAG(Tag, boost::mpl::_)>::type iter_##Tag;                    \
    typedef typename boost::mpl::eval_if_c<boost::is_same<iter_##Tag, typename boost::mpl::end<Parameters>::type>::value,   \
                                           boost::mpl::identity<Default>,                                                   \
                                           boost::mpl::deref<iter_##Tag>>::type Tag;

    
template <typename A0 = Void, typename A1 = Void>
struct ColorFormat {
    typedef boost::mpl::vector<A0, A1> Parameters;
    
    GET_OR_DEFAULT(BoundingBoxPolicy, ::BoundingBoxPolicy::Last)
    GET_OR_DEFAULT(ConversionDir, ::ConversionDir::Direct)
};



#include <iostream>

int main() {
    {
        typedef ColorFormat<BoundingBoxPolicy::All, ConversionDir::Inverse> ColorFormat;
        std::cout << boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::All>::value << std::endl;
        std::cout << boost::is_same<ColorFormat::ConversionDir, ConversionDir::Inverse>::value << std::endl;
    }
    {
        typedef ColorFormat<ConversionDir::Inverse, BoundingBoxPolicy::All> ColorFormat;
        std::cout << boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::All>::value << std::endl;
        std::cout << boost::is_same<ColorFormat::ConversionDir, ConversionDir::Inverse>::value << std::endl;
    }
    {
        typedef ColorFormat<ConversionDir::Inverse> ColorFormat;
        std::cout << boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::Last>::value << std::endl;
        std::cout << boost::is_same<ColorFormat::ConversionDir, ConversionDir::Inverse>::value << std::endl;
    }
    {
        typedef ColorFormat<> ColorFormat;
        std::cout << boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::Last>::value << std::endl;
        std::cout << boost::is_same<ColorFormat::ConversionDir, ConversionDir::Direct>::value << std::endl;
    }
    {
        typedef ColorFormat<> ColorFormat;
        std::cout << !boost::is_same<ColorFormat::BoundingBoxPolicy, BoundingBoxPolicy::All>::value << std::endl;
        std::cout << !boost::is_same<ColorFormat::ConversionDir, ConversionDir::Inverse>::value << std::endl;
    }
}