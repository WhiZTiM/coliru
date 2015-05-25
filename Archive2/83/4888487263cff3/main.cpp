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

    template <class Archive> void serialize(Archive &, const unsigned int) {
        std::cerr << __PRETTY_FUNCTION__ << "\n";
    }

    template <class Archive, typename K> inline friend void save_construct_data(Archive& ar, std::pair<K, Foo> const* v, const unsigned int) {
        std::cerr << __PRETTY_FUNCTION__ << "\n";
        ar & boost::serialization::make_nvp("first", v->first);
        ar & boost::serialization::make_nvp("second", v->second.i);
    }
    template <class Archive, typename K> inline friend void load_construct_data(Archive& ar, std::pair<K, Foo>* v, const unsigned int) {
        std::cerr << __PRETTY_FUNCTION__ << "\n";
        typename std::remove_cv<K>::type first;
        ar & boost::serialization::make_nvp("first", first);
        int tmp;
        ar & boost::serialization::make_nvp("second", tmp);
        new(v) std::pair<K, Foo>(first, tmp);
    }

    int i;

  public:
    Foo(int k) : i(k) {}

    friend std::ostream& operator<<(std::ostream& os, Foo const& foo) {
        return os << "Foo { " << foo.i << " }";
    }
};

namespace boost { namespace serialization {


} }

int main() {
    using Data = std::map<std::string, Foo>;
    std::cout << "Boost version: " << BOOST_VERSION << "\n";

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
