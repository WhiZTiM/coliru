#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/access.hpp>

template <typename T>
class A {
  public:
    A(const T &id) : m_id(id) {}

    T& getRef()             { return m_id; } 
    T const& getRef() const { return m_id; } 
  private:
    T m_id;
};

namespace boost {
namespace serialization {
    template <class Archive, typename T>
    void serialize(Archive &ar, A<T> &a, const unsigned int)
    {
        ar & boost::serialization::make_nvp("m_id", a.getRef());
    }
}
}

int main() {
    A<int> a(42);
    boost::archive::xml_oarchive oa(std::cout);
    oa << BOOST_SERIALIZATION_NVP(a);
}
