#include <boost/icl/interval_map.hpp>
#include <set>

namespace icl = boost::icl;

using Container = icl::interval_map<
    size_t,          // mirrors the vector index
    std::set<int> >; // set intersection models our "overlap"

Container generate_random_data();

#include <iostream>

int main() {
    auto haystack = generate_random_data();

    // let's find all ranges where the T overlaps with -2:
    
    using Seive = Container::value_type;

    std::cout << "Haystack: " << haystack << "\n";
    std::cout << "Overlaps -2: \n\t-> " << (haystack & Seive {{ 0, 1024 }, { -2 }}) << "\n";
    std::cout << "Overlaps +7: \n\t-> " << (haystack & Seive {{ 0, 1024 }, { +7 }}) << "\n";

    // you can even do a "multi-sieve" in one pass:
    std::cout << "Overlaps any of +7 or -2: \n\t-> " << (haystack & Seive {{ 0, 1024 }, { -2, +7 }}) << "\n";

    // and more interesting, you can narrow any of the "overlap" targets to a certain input range:
    Container combined;
    combined += Seive {{ 128, 512 }, { -2 }};
    combined += Seive {{ 512, 768 }, { +7 }};
    std::cout << "Complex query " << combined << ": \n\t-> " << (haystack & combined) << "\n";
}

#include <random>
#include <functional>

Container generate_random_data() {
    using namespace std;

    mt19937 prng {3236629322}; // random_device{}();
    auto card     = bind(uniform_int_distribution<>(1,       5),    ref(prng));
    auto domain   = bind(uniform_int_distribution<size_t>(0, 1024), ref(prng));
    auto codomain = bind(uniform_int_distribution<>(-10,     10),   ref(prng));
    auto gen_val  = [&] { 
        Container::value_type::second_type v;
        generate_n(inserter(v, end(v)), card(), codomain);
        return v;
    };

    auto gen_range = [&]() -> Container::value_type { 
        auto left = domain(), right = domain();
        if (left>right) swap(left, right);

        return { 
            Container::interval_type::right_open ( left, right ),
            gen_val()
        };
    };

    {
        Container data;
        generate_n(icl::inserter(data, end(data)), prng() % 1024, gen_range);
        return data;
    }
}
