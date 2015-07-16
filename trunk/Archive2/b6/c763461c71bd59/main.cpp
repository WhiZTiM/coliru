#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <boost/crc.hpp>
#include <cassert>

template <size_t N>
uint32_t crc32_n(std::bitset<N> const& bs, size_t n) {
    assert(n <= N);

    std::string const s = bs.template to_string<char>();
    auto f = s.begin();

    return std::for_each(f, f+n, boost::crc_32_type{})();
}

int main() {
    std::bitset<112> b_data;

    // set some random data (above the first 32 bits that are for CRC)  
    srand(time(0));
    b_data.set(rand()%80 + 32);

    auto const crc = crc32_n(b_data, 80);

    std::cout << crc                 << ":\t" << b_data << "\n";
    b_data |= crc;
    std::cout << crc32_n(b_data, 80) << ":\t" << b_data << "\n";
}
