#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/access.hpp>

template <typename T>
class A {
  public:
    A(const T &id) : m_id(id) {}
  private:
    template <typename Ar, typename U> friend void boost::serialization::serialize(Ar&,A<U>&,const unsigned);
    T m_id;
};

namespace boost {
namespace serialization {
    template <class Archive, typename T>
    void serialize(Archive &ar, A<T> &a, const unsigned int)
    {
        ar & BOOST_SERIALIZATION_NVP(a.m_id);
    }
}
}

int main() {
    A<int> a(42);
    boost::archive::xml_oarchive oa(std::cout);
    oa << BOOST_SERIALIZATION_NVP(a);
}
