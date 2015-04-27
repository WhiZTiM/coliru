#include <iostream>
#include <bitset>

template <typename T>
T twos_complement(T bs) {
    return T((~bs).to_ulong() + 1);
}

template <std::size_t N>
struct bits {
    bits(unsigned long b) : b{b} { }
    
    bits 
    operator ~ () const {
        return {~b};
    }
    
    unsigned long
    to_ulong() const {
        return b;
    }
    
    operator std::bitset<N> () {
        return {b};
    }
    
    unsigned long b;
};

int
main() {
    std::cout << static_cast<std::bitset<4>>(twos_complement(bits<4>{13})) << '\n';
}
