#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/version.hpp>
#include <fstream>
#include <iostream>

class Foo {
    friend class boost::serialization::access;

#if 0
    Foo() = default;
    template <class Archive> void serialize(Archive &, const unsigned int) {
        std::cerr << __PRETTY_FUNCTION__ << "\n";
    }

    template <class Archive> inline friend void save_construct_data(Archive& ar, Foo const* v, const unsigned int) {
        std::cerr << __PRETTY_FUNCTION__ << "\n";
        ar & boost::serialization::make_nvp("i", v->i); }
    template <class Archive> inline friend void load_construct_data(Archive& ar, Foo* v, const unsigned int) {
        std::cerr << __PRETTY_FUNCTION__ << "\n";
        int tmp;
        ar & boost::serialization::make_nvp("i", tmp);
        new(v) Foo(tmp);
    }
#else
    Foo() = default;
    template <class Archive> void serialize(Archive &ar, const unsigned int) {
        ar & BOOST_SERIALIZATION_NVP(i);
    }
#endif
    int i;

  public:
    Foo(int k) : i(k) {}

    friend std::ostream& operator<<(std::ostream& os, Foo const& foo) {
        return os << "Foo { " << foo.i << " }";
    }
};

int main() {
    using Data = std::map<std::string, Foo>;
    //std::cout << BOOST_VERSION << "\n";

    {
        auto f = Data { {"a", 12 }, {"b", 42} };
        //for (auto& e : f) std::cout << e.first << ", " << e.second << "\n";
        std::ofstream os("path");
        boost::archive::xml_oarchive oa(os);
        oa << boost::serialization::make_nvp("f", f);
    }

    {
        Data g;
        std::ifstream is("path");
        boost::archive::xml_iarchive ia(is);
        ia >> boost::serialization::make_nvp("f", g);

        for (auto& e : g)
            std::cout << e.first << ", " << e.second << "\n";
    }
}
