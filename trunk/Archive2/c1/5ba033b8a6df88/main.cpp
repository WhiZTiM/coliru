#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

#include <boost/serialization/access.hpp>

struct A {
    int simple;

  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned) {
        ar & simple;
    }
};

struct B {
    std::string text;

  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned) {
        ar & text;
    }
};

struct C {
    A composed_a;
    B composed_b;

  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned) {
        ar & composed_a & composed_b;
    }
};

struct FileContents { // conventions...
    boost::variant<A, B, C> payload;

  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned) {
        ar & payload;
    }
};


#include <sstream>
#include <boost/lexical_cast.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// For our roundtrip test, implement streaming as well so we can independently check equivalence
inline static std::ostream& operator<<(std::ostream& os, A const& v) {
    return os << "A{" << v.simple << "}";
}
inline static std::ostream& operator<<(std::ostream& os, B const& v) {
    return os << "B{" << v.text << "}";
}
inline static std::ostream& operator<<(std::ostream& os, C const& v) {
    return os << "C{" << v.composed_a << ", " << v.composed_b << "}";
}

void roundtrip_test(FileContents const& original) {
    std::stringstream ss;
    {
        boost::archive::text_oarchive oa(ss);
        oa << original;
    }

    {
        boost::archive::text_iarchive ia(ss);

        FileContents clone;
        ia >> clone;
        
        std::string const before = boost::lexical_cast<std::string>(original.payload);
        std::string const after  = boost::lexical_cast<std::string>(clone.payload);

        std::cout << "Roundtrip '" << before << "': " << std::boolalpha << (before == after) << "\n";
    }
}

int main() {
    roundtrip_test({ A { 42 } });
    roundtrip_test({ B { "Life The Universe And Everything" } });
    roundtrip_test({ C { {42}, { "Life The Universe And Everything" } } });
}
