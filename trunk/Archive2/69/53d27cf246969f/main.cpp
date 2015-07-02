#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <iostream>
#include <sstream>

int main() {
    // Serialization for double* does not compile
    double* p(new double(2.0));
    std::cout << *p << std::endl;

    std::ostringstream oss;
    boost::archive::xml_oarchive oa(oss);
    oa << BOOST_SERIALIZATION_NVP(p); 
    std::cout << oss.str() << std::endl;
}

