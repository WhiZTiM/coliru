#include <iostream>
#include <iterator>
#include <vector>
#include <cstdint>

int main() {

    std::uint64_t alpha = 0x00000000000042ab;
    std::size_t sizeOfAlpha = 2u, i = 1u;
    
    std::vector<std::uint8_t> vec(8);
    
    for(std::size_t j = (i + 1u) * sizeOfAlpha - 1u; sizeOfAlpha; --j, --sizeOfAlpha) {
        vec[j] = alpha & 0xff;
        alpha >>= 8;
    }
    
    std::cout << std::hex;
    std::copy(begin(vec), end(vec), std::ostream_iterator<unsigned int>(std::cout, " "));
    std::cout << '\n';

    return 0;
}
