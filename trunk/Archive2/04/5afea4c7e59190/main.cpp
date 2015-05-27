#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/optional.hpp>

struct MyType {
    MyType();
    MyType(std::string const& v);

  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar&, unsigned);

#if DEMO_VERSION == 0

    bool hasValue;
    std::string value;

#elif DEMO_VERSION == 1

    boost::optional<std::string> value;

#endif
};

BOOST_CLASS_VERSION(MyType, DEMO_VERSION)

#if DEMO_VERSION == 0
MyType::MyType()                     : hasValue(false)          {}
MyType::MyType(std::string const &v) : hasValue(true), value(v) {}

template <typename Ar> void MyType::serialize(Ar& ar, unsigned /*file_version*/) {
    ar & hasValue & value; // life was simple in v0
}

#elif DEMO_VERSION == 1
MyType::MyType()                     : value(boost::none)       {}
MyType::MyType(std::string const &v) : value(v)                 {}

template <typename Ar> void MyType::serialize(Ar& ar, unsigned file_version) {
    switch (file_version) {
        case 0: {
            assert(Ar::is_loading::value); // should not be writing old formats
            //
            bool        old_hasValue;      // these fields no longer exist
            std::string oldValue;

            ar & old_hasValue & oldValue;

            // translate to new object semantics/layout
            value.reset();
            if (old_hasValue) value.reset(oldValue);

            break;
        }
        default: // v1+
            ar & value;
    }
}
#endif

#include <fstream>

namespace demo {
    template <typename T> void serialize(std::ostream& os, T const& obj) {
        {
            boost::archive::text_oarchive oa(os);
            oa << obj;
        }
        os.flush();
    }

    template <typename T> void save(std::string const& fname, T const& payload) {
        std::ofstream ofs(fname, std::ios::binary);
        serialize(ofs, payload);
    }

    MyType load(std::string const& fname) {
        std::ifstream ifs(fname, std::ios::binary);

        MyType obj;

        boost::archive::text_iarchive ia(ifs);
        ia >> obj;

        return obj;
    }
}

int main(int, char** cmd) {
    std::cout << "Running " << *cmd << " with DEMO_VERSION=" << DEMO_VERSION << "\n";
    using namespace demo;

#if DEMO_VERSION == 0

    MyType payload("Forty two");
    save     ("v0.dat", payload);  // uses v0 format
    serialize(std::cout, payload); // uses v0 format

#elif DEMO_VERSION == 1

    auto loaded = load("v0.dat");  // still reads the v0 format
    serialize(std::cout, loaded);  // uses v1 format now

#endif
}
