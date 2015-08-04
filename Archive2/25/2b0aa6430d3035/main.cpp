#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

struct A {
    A(int aa) : a(aa) {}
    int a;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& BOOST_SERIALIZATION_NVP(a);
    }
};

template <typename T>
struct Ptr { // Ptr could use init constructor here but this is not the point
    Ptr() { m_elem = 0; }
    Ptr(const T* elem) {
        if (elem)
            m_elem = new T(*elem);
        else
            m_elem = 0;
    }
    Ptr(const T& elem)
    {
    	m_elem = new T(elem);
	}
    Ptr(const Ptr& elem)
	{
		if (elem.m_elem)
			m_elem = new T(*(elem.m_elem));
		else
			m_elem = 0;
	}
    virtual ~Ptr() { delete m_elem; m_elem = 0; };
    
    const T& operator*() const { return *m_elem; };
    T& operator*() { return *m_elem; };

    const T* operator->() const { return m_elem; };
    T* operator->() { return m_elem; };

    T* m_elem;
};

namespace boost { namespace serialization {
    
    // Not sure about the approach to manage null m_elem here
    template<class Archive, class T>
    void save(Archive & ar, const Ptr<T> &ptr, const unsigned int version)
    {
        T elem = 0;
        if (ptr.m_elem != 0)
            ar& boost::serialization::make_nvp("data", *ptr.m_elem);
        else
            ar& boost::serialization::make_nvp("data", elem);
    }
    
    // How to implement load ?
    template<class Archive, class T>
    void load(Archive & ar, Ptr<T> &ptr, const unsigned int version)
    {
        T *elem;
    	ar & boost::serialization::make_nvp("data", elem);
    }
    
    template<class Archive, class T>
    void serialize(Archive & ar, Ptr<T> &ptr, const unsigned int version)
    {
    	boost::serialization::split_free(ar, ptr, version);
    }

}} // end namespace


int main()
{
    {
        Ptr<A> p;
        std::ostringstream oss;
        boost::archive::xml_oarchive oa(oss);
        oa << BOOST_SERIALIZATION_NVP(p);
        std::cout << oss.str() << std::endl;
        
        // The deserialization gives a compiler error here
        /*
        Ptr<double> po;
        std::istringstream iss;
        iss.str(oss.str());
        boost::archive::xml_iarchive ia(iss);
        ia >> BOOST_SERIALIZATION_NVP(po);
        */
    }
    {
        Ptr<double> p(new double(2.0));
        std::cout << *(p.m_elem) << std::endl;

        std::ostringstream oss;
        boost::archive::xml_oarchive oa(oss);
        oa << BOOST_SERIALIZATION_NVP(p);
        std::cout << oss.str() << std::endl;
        
        // The deserialization gives a compiler error here
        /*
        Ptr<double> po;
        std::istringstream iss;
        iss.str(oss.str());
        boost::archive::xml_iarchive ia(iss);
        ia >> BOOST_SERIALIZATION_NVP(po);
        */
    }
}
