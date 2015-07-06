#include <vector>
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
};

template<class V, class T>
struct Derived : public Base<V, int>, public Base<V, std::string> {
    Derived(T tt) : Base<V, int>(2.0, 4), Base<V, std::string>(3.0, std::string("hello")), t(tt) {}
    T t;
};

// does not work
//BOOST_CLASS_EXPORT(Derived);

namespace boost { namespace serialization {

template<class Archive, class U, class V>
void serialize(Archive & ar, Base<U,V> &obj, const unsigned int version) {
    ar& BOOST_SERIALIZATION_NVP(obj.u);
    ar& BOOST_SERIALIZATION_NVP(obj.v);
}

template<class Archive, class V, class T>
void serialize(Archive & ar, Derived<V,T> &obj, const unsigned int version) {
    boost::serialization::make_nvp("Base1", 
    	boost::serialization::base_object<Base<V, int>>(obj) );
    boost::serialization::make_nvp("Base2", 
        boost::serialization::base_object<Base<V, std::string>>(obj) );
    // does not work
    // ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base<V, int>); 
    // ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base<V, std::string>);
    ar& BOOST_SERIALIZATION_NVP(obj.t);
}

}} // end namespace

int main() {
    Derived<double, int> a(10);

	std::ostringstream archive_ostream;
	boost::archive::xml_oarchive oa(archive_ostream);
	oa << BOOST_SERIALIZATION_NVP(a); 
    std::cout << archive_ostream.str() << std::endl;
}

