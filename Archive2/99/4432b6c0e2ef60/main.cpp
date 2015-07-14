#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/type_index.hpp>
#include <iostream>
#include <sstream>

struct MB_BPMessage {
    int some=1, common=2, fields=3;

    std::string key() const { return boost::lexical_cast<std::string>(boost::tie(some,common,fields)); }

  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned) { ar & some & common & fields; }
};

struct MB_BPRequest : MB_BPMessage {
    int request_x=444;

    std::string key() const { return boost::lexical_cast<std::string>(boost::make_tuple(request_x,MB_BPMessage::key())); }

  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned) { ar & boost::serialization::base_object<MB_BPMessage>(*this) & request_x; }
};

struct MB_BPResponse : MB_BPMessage {
    int response_x=555;

    std::string key() const { return boost::lexical_cast<std::string>(boost::make_tuple(response_x,MB_BPMessage::key())); }

  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned) { ar & boost::serialization::base_object<MB_BPMessage>(*this) & response_x; }
};

// out test function; serialize from any specific type to any other type
// The trick is that we can deduce both if left unspecified
template <typename From, typename To = From>
void test_roundtrip(From const& from) {
    std::stringstream ss;
    {
        boost::archive::binary_oarchive oa(ss);
        oa << from;
    }

    {
        boost::archive::binary_iarchive ia(ss);
        To to;
        ia >> to;

        // verify roundtrip
        bool ok = (from.key() == to.key());
        std::cout << __PRETTY_FUNCTION__ << "\troundtrip ok: " << std::boolalpha << ok << "\n";
        std::cout << "From: " << boost::typeindex::type_id_with_cvr<From>().pretty_name() << ", key: " << from.key() << "\n";
        std::cout << "To:   " << boost::typeindex::type_id_with_cvr<To  >().pretty_name() << ", key: " << from.key() << "\n";
        std::cout << "--\n";
    }
}

int main() {
    MB_BPMessage  message;
    MB_BPRequest  request;
    MB_BPResponse response;

    std::cout << "---- matching lvalue references: all ok\n";
    test_roundtrip(message);
    test_roundtrip(request);
    test_roundtrip(response);

    std::cout << "\n---- through base&: matching, but only serializing the base fields!\n";
    test_roundtrip<MB_BPMessage>(message);
    test_roundtrip<MB_BPMessage>(request);
    test_roundtrip<MB_BPMessage>(response);

    std::cout << "\n---- through base&: matching, but only serializing the base fields!\n";
    test_roundtrip<MB_BPMessage>(message);
    test_roundtrip<MB_BPRequest,  MB_BPMessage>(request);
    test_roundtrip<MB_BPResponse, MB_BPMessage>(response);
}
