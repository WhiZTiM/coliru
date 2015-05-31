#include <boost/dynamic_bitset.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <stdexcept>

template <typename T, typename Alloc, typename Rnd = boost::mt19937>
size_t select_random_bit(boost::dynamic_bitset<T, Alloc> const& bs, Rnd& random, bool target = true) {
    boost::uniform_int<size_t> pick(0,bs.size()-1);

    if (bs.empty() || (bs.all() && !target) || (bs.none() && target))
        throw std::range_error("select_random_bit");

    while(true) {
        auto index = pick(random);
        if (bs[index] == target)
            return index;
    }

    throw std::logic_error("select_random_bit");
}

boost::dynamic_bitset<> generate_testdata(boost::mt19937& rng) {
    boost::dynamic_bitset<> bs(1024+rng()%1024); // [1024,2048) bits

    boost::uniform_smallint<uint8_t> gen(0, 1);
    for(size_t i = 0; i < bs.size(); ++i)
        bs[i] = gen(rng);

    return bs;
}

int main() {
    using namespace boost;

    mt19937 rng(42); // seed it
    auto data = generate_testdata(rng);

    std::cout << data.count() << " out of " << data.size() << " bits are set\n";

    std::cout << "\nTrue: ";
    for (int i = 0; i <10; ++i)
        std::cout << select_random_bit(data, rng/*, true*/) << " ";

    std::cout << "\nFalse: ";
    for (int i = 0; i <10; ++i)
        std::cout << select_random_bit(data, rng, false) << " ";
}
