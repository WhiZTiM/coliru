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
    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& BOOST_SERIALIZATION_NVP(a);
    }
};

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
    // Serialization for Ptr<double> can compile
    {
        Ptr<double> p(new double(2.0));
        std::cout << *(p.m_elem) << std::endl;

        std::ostringstream oss;
        boost::archive::xml_oarchive oa(oss);
        oa << BOOST_SERIALIZATION_NVP(p);
        std::cout << oss.str() << std::endl;
    }
}
