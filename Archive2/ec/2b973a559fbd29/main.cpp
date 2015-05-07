#include <iostream>
#include <iomanip>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_int/serialize.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>

#include <boost/functional/hash.hpp>

namespace mp_hashing {
    namespace io = boost::iostreams;

    struct hash_sink {
        hash_sink(size_t& seed_ref) : _ptr(&seed_ref) {}

        typedef char         char_type;
        typedef io::sink_tag category;

        std::streamsize write(const char* s, std::streamsize n) {
            boost::hash_combine(*_ptr, boost::hash_range(s, s+n));
            return n;
        }
      private:
        size_t* _ptr;
    };

    template <typename T> struct hash_impl {
        size_t operator()(T const& v) const {
            using namespace boost;
            size_t seed = 0;
            {
                iostreams::stream<hash_sink> os(seed);
                archive::binary_oarchive oa(os, archive::no_header | archive::no_codecvt);
                oa << v;
            }
            return seed;
        }
    };
}

#include <unordered_map>
#include <boost/unordered_map.hpp>

namespace std {
    template <typename backend> 
    struct hash<boost::multiprecision::number<backend> > 
        : mp_hashing::hash_impl<boost::multiprecision::number<backend> > 
    {};
}

namespace boost {
    template <typename backend> 
    struct hash<multiprecision::number<backend> > 
        : mp_hashing::hash_impl<multiprecision::number<backend> > 
    {};
}

template <typename Map>
void test(Map const& map) {
    std::cout << "\n" << __PRETTY_FUNCTION__ << "\n";
    for(auto& p : map)
        std::cout << p.second << "\t" << p.first << "\n";
}

int main() {
    using boost::multiprecision::cpp_int;

    test(std::unordered_map<cpp_int, std::string> {
        { cpp_int(1) << 111, "one"   },
        { cpp_int(2) << 222, "two"   },
        { cpp_int(3) << 333, "three" },
    });

    test(boost::unordered_map<cpp_int, std::string> {
        { cpp_int(1) << 111, "one"   },
        { cpp_int(2) << 222, "two"   },
        { cpp_int(3) << 333, "three" },
    });
}
