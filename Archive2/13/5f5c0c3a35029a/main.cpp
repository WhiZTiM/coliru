#include <sstream>
#include <iostream>

#include <boost/serialization/nvp.hpp>
#include <boost/archive/text_oarchive.hpp>

struct test {
    unsigned int value;

    template<class Archive>
    void serialize(Archive & ar, unsigned int const version)
    {
        ar & BOOST_SERIALIZATION_NVP(value);
    }
};

int main() {
    test a{42};
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << BOOST_SERIALIZATION_NVP(a);
    std::cout << ss.str() << std::endl;
    return 0;
}
