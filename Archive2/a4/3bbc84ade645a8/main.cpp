#include <string>
#include <iostream>
#include <sstream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp>

template<class U, class V>
struct Base {
    Base(U uu, V vv) : u(uu), v(vv) {}
    U u;
    V v;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
    ar& BOOST_SERIALIZATION_NVP(u);
    ar& BOOST_SERIALIZATION_NVP(v);
}

};

template<class V, class T>
struct Derived : public Base<V, int>, public Base<V, std::string> {
    Derived(T tt) : Base<V, int>(2.0, 4), Base<V, std::string>(3.0, std::string("hello")), t(tt) {}
    T t;
    
    
template<class Archive>
void serialize(Archive & ar,  const unsigned int version) {

typedef Base<V, int> Base1; 
typedef Base<V, std::string> Base2; 
ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base1);
ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base2);
        

    ar& BOOST_SERIALIZATION_NVP(t);
}
};


int main() {
    Derived<double, int> a(10);

	std::ostringstream archive_ostream;
	boost::archive::xml_oarchive oa(archive_ostream);
	oa << BOOST_SERIALIZATION_NVP(a); 
    std::cout << archive_ostream.str() << std::endl;
}

