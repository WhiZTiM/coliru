#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <iostream>
#include <sstream>
#include <string>

template <typename T>
struct Ptr {
    Ptr() : m_elem(0) {}
    Ptr(const T* elem) { m_elem = (elem ? new T(*elem) : 0); };

    const T& operator*() const { return *m_elem; };
    T& operator*() { return *m_elem; };

    const T* operator->() const { return m_elem; };
    T* operator->() { return m_elem; };

    // [...] other ctor, copy, del, etc...

    T* m_elem;
};

namespace boost {
    namespace serialization {
        template <class Archive, class T>
            void serialize(Archive& ar, Ptr<T>& ptr, const unsigned int /*version*/)
            {
                ar& boost::serialization::make_nvp("data", *ptr.m_elem);
            }
    }
} // end namespace

int main()
{
    std::stringstream ss;

    {
        Ptr<double> p(new double(2.0));
        std::cout << *(p.m_elem) << std::endl;

        boost::archive::xml_oarchive oa(ss);
        oa << BOOST_SERIALIZATION_NVP(p);
        std::cout << ss.str() << std::endl;
    }

    {
        Ptr<double> p(nullptr);

        boost::archive::xml_iarchive ia(ss);
        ia >> BOOST_SERIALIZATION_NVP(p);
        std::cout << *p.m_elem << std::endl;
    }

}
