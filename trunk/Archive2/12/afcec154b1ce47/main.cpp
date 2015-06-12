#include <boost/optional.hpp>
#include <iostream>
#include <vector>
#include <bitset>
#include <boost/dynamic_bitset.hpp>

template <size_t N>
struct X {
    struct Options1 {
        boost::optional<int64_t> options[N];
    };

    struct Options2 {
        int64_t options_[N];
        bool enabled[N];
    };

    struct Options3 {
        int64_t options_[N];
        std::bitset<N> enabled;
    };

    struct Options4 {
        int64_t options_[N];
        boost::dynamic_bitset<> enabled {N};
    };
};

int main() {
    std::cout << sizeof(X< 8>::Options1) << "\t"
              << sizeof(X< 8>::Options2) << "\t"
              << sizeof(X< 8>::Options3) << "\t"
              << sizeof(X< 8>::Options4) << std::endl;

    std::cout << sizeof(X<80>::Options1) << "\t"
              << sizeof(X<80>::Options2) << "\t"
              << sizeof(X<80>::Options3) << "\t"
              << sizeof(X<80>::Options4) << std::endl;

    std::cout << sizeof(X<800>::Options1) << "\t"
              << sizeof(X<800>::Options2) << "\t"
              << sizeof(X<800>::Options3) << "\t"
              << sizeof(X<800>::Options4) << std::endl;
}
