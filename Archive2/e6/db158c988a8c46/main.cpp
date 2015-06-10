#include <iostream>
#include <exception>
#include <sstream>
#include <boost/archive/xml_oarchive.hpp>

enum e_fruit {
   apple,
   banana,
   coconut
};

template<typename T>
T to_enum(std::string const &str) {
    return T();
}

std::string to_string(e_fruit e) {
    if(e == apple) return "apple";
    return "";
}

struct fruit_basket {
   e_fruit fruit;
   int     num;
};

template<typename T>
struct enum_wrapper {
    T &_e;
    enum_wrapper(T &e) : _e(e) {}
    
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const  {
        std::string str_v = to_string(_e);
        ar & BOOST_SERIALIZATION_NVP(str_v);
    }
    
    template<class Archive>
    void load(Archive & ar, const unsigned int version) {
        std::string str_v;
        ar & BOOST_SERIALIZATION_NVP(str_v);
        _e = to_enum<T>(str_v);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

template<typename T>
enum_wrapper<T> wrap(T& e) { return enum_wrapper<T>(e); }

namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive & ar, fruit_basket & b, const unsigned int version)
{
    auto w = wrap(b.fruit);
    ar & BOOST_SERIALIZATION_NVP(w);
    ar & BOOST_SERIALIZATION_NVP(b.num);
}

} // namespace serialization
} // namespace boost

int main() {
   fruit_basket bsk;
   bsk.fruit = apple;
   bsk.num = 5;
   
   std::stringstream strstr;
   boost::archive::xml_oarchive oa(strstr);
   oa << BOOST_SERIALIZATION_NVP(bsk);
   
   std::cout << strstr.str() << std::endl;
}
