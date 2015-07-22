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

// for demo purposes only
void process_payload_switch(FileContents&);
void process_payload_visitor(FileContents&);

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

        std::cout << "\nRoundtrip '" << before << "': " << std::boolalpha << (before == after) << "\n";
        process_payload_switch(clone);
        process_payload_visitor(clone);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Showing how to use boost::variant (on the consuming end)
void process_payload_switch(FileContents& contents) {
    switch(contents.payload.which())
    {
        case 0: 
            {
                A& actual_data = boost::get<A>(contents.payload);
                std::cout << __FUNCTION__ << " processing an instance of A (" << actual_data.simple << ")\n";
                break;
            }
        case 1: 
            {
                B& actual_data = boost::get<B>(contents.payload);
                std::cout << __FUNCTION__ << " processing an instance of B (" << actual_data.text << ")\n";
                break;
            }
        case 2: 
            {
                C& actual_data = boost::get<C>(contents.payload);
                std::cout << __FUNCTION__ << " processing an instance of C\n";
                break;
            }
        default:
                std::cout << __FUNCTION__ << " NOT IMPLEMENTED\n";
    }
}

void process_payload_visitor(FileContents& contents) {
    
    struct visitor : boost::static_visitor<std::string> {
        std::string operator()(A const&) const   { return "(type is A)"; }
        std::string operator()(B const& b) const { return "(type is B with text: '" + b.text + "')"; }
        std::string operator()(C const& c) const { 
            std::ostringstream oss;
            oss << "(type is C: '" << c << "'";
            return oss.str();
        }
    };

    std::cout << __FUNCTION__ << " processing: " << boost::apply_visitor(visitor(), contents.payload) << "\n";
}

int main() {
    roundtrip_test({ A { 42 } });
    roundtrip_test({ B { "Life The Universe And Everything" } });
    roundtrip_test({ C { {42}, { "Life The Universe And Everything" } } });
}
