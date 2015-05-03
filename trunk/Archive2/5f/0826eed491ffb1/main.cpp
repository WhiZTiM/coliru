#include <boost/serialization/map.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/random.hpp>
#include <boost/bind.hpp>

struct myParam { 
    std::string data; 
    template <typename Ar> void serialize(Ar& ar, unsigned) {
        ar & data;
    }
};

static inline std::string generate_value() {
    static auto rand_char = boost::bind(boost::uniform_int<unsigned char>(0,255), boost::mt19937{});

    std::string s;
    std::generate_n(back_inserter(s), rand_char(), rand_char);
    return s;
}

using Map = std::map<unsigned int,myParam>;

Map generate_data(unsigned n) {
    Map map;

    for (unsigned i=0; i<n; ++i)
        map.emplace(i, myParam { generate_value() });

    return map;
}

#include <fstream>
#include <iostream>

int main() {
    {
        std::ofstream ofs("/tmp/all_params", std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);

        auto data = generate_data(10ul<<3);
        oa << data;
        std::cout << "Serialized " << data.size() << " entries\n";
    }
}
