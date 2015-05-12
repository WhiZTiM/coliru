#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <sstream>

class base {
  public:
    base(int v1) : v1(v1) {}
    virtual void bla() const = 0;

  private:
    friend class boost::serialization::access;

    template <class Archive> void serialize(Archive &ar, unsigned /*int const file_version*/) {
        ar & BOOST_SERIALIZATION_NVP(v1);
    }
  protected:
    int v1;
};

class derived : public base {
  public:
    derived(int v1 = 10, int v2 = 100) : base(v1), v2(v2) {}
    virtual void bla() const {
        std::cout << "v1: " << v1 << ", v2: " << v2 << "\n";
    }

  private:
    friend class boost::serialization::access;
    int v2;
    template <class Archive> void serialize(Archive &ar, unsigned /*int const file_version*/) {
        boost::serialization::base_object<base>(*this);
        ar & BOOST_SERIALIZATION_NVP(v2);
    }
};

BOOST_CLASS_EXPORT(base)
BOOST_CLASS_EXPORT(derived)

int main() {
    std::stringstream ss;
    {
        boost::archive::text_oarchive ar(ss);
        base *b = new derived();
        ar << boost::serialization::make_nvp("base", b);
    }

    std::cout << ss.str() << std::endl;
    base *deserialized = nullptr;
    {
        boost::archive::text_iarchive ar1(ss);
        ar1 >> boost::serialization::make_nvp("base", deserialized);
    }

    deserialized->bla();
}
