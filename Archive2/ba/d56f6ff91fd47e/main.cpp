#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

struct A { 
    A(int aa) : a(aa) {} 
    int a; 
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & BOOST_SERIALIZATION_NVP(a);
    }
};
    
template <typename T>
struct Ptr {
    Ptr() : m_elem(0) {}
	Ptr(const T* elem) { m_elem = (elem ? new T(*elem) : 0); };
	const T& operator*() const { return *m_elem; };
	T& operator*()	{ return *m_elem; };
	const T* operator->() const { return m_elem;};
	T* operator->()	{ return m_elem;};

	// [...] other ctor, copy, del, etc...

	T* m_elem;
};

namespace boost { namespace serialization {

template<class Archive, class T>
void save(Archive & ar, const Ptr<T> &ptr, const unsigned int version)
{
	//const T *const base_pointer = new T(*(ptr.m_elem));
	T* base_pointer = (ptr.m_elem);
	ar & boost::serialization::make_nvp("Ptr", base_pointer);
}

template<class Archive, class T>
void load(Archive & ar, Ptr<T> &ptr, const unsigned int version)
{
    T *base_pointer;
	ar & boost::serialization::make_nvp("Ptr", base_pointer);
    ptr.m_elem = base_pointer;
}

template<class Archive, class T>
void serialize(Archive & ar, Ptr<T> &ptr, const unsigned int version)
{
	//ar &BOOST_SERIALIZATION_NVP(ptr.m_elem);
	boost::serialization::split_free(ar, ptr, version);
}

}} // end namespace

int main() {
	Ptr<A> p1(new A(4));
	std::cout << p1.m_elem->a << std::endl;
	Ptr<double> p2(new double(2.0));
	std::cout << *(p2.m_elem) << std::endl;

    // The serialization for Ptr<A> seems to work
	std::ostringstream archive_ostream;
	boost::archive::xml_oarchive oa(archive_ostream);
	oa << BOOST_SERIALIZATION_NVP(p1); 
    std::cout << archive_ostream.str() << std::endl;
    
    // Serialization for Ptr<double> does not compile
    /*
    std::ostringstream archive_ostream2;
    boost::archive::xml_oarchive oa2(archive_ostream2);
    oa2 << BOOST_SERIALIZATION_NVP(p2); 
    std::cout << archive_ostream2.str() << std::endl;
    */
}

