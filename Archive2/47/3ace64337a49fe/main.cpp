#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <fstream>

class Foo {
    friend class boost::serialization::access;
    template <class Archive> void serialize(Archive &ar, const unsigned int) { ar &BOOST_SERIALIZATION_NVP(i); }
    Foo() : i(0) {}
    int i;

  public:
    Foo(int k) : i(k) {}
};

int main(int argc, char *argv[]) {
    std::vector<Foo> f;
    f.push_back(Foo(12));
    std::ofstream os("path");
    boost::archive::xml_oarchive oa(os);
    oa << boost::serialization::make_nvp("f", f);
    os.close();
    std::vector<Foo> g;
    std::ifstream is("path");
    boost::archive::xml_iarchive ia(is);
    ia >> boost::serialization::make_nvp("f", g);
}
