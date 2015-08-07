#include <cstddef>
#include <iostream>
#include <algorithm>
#include <initializer_list>

// Own implementation as std::array::operator[] is not constexpr :/
template <typename T, std::size_t N>
struct array
{
    constexpr T& operator[] (std::size_t index) { return data[index];}
    constexpr const T& operator[] (std::size_t index) const { return data[index];}

    constexpr std::size_t size() const { return N; }

    T data[N];
};

constexpr array<std::size_t, 1001u> make_bottle_count()
{
    array<std::size_t, 1001u> a = {{0, 1, 2, 3, 4, 1, 2, 1, 2, 3, 1}};
    for (int i = 11; i != a.size(); ++i) {
        auto il = {a[i - 1], a[i - 5], a[i - 7], a[i - 10]};
        if(begin(il)[0] != a[i-1] || begin(il)[1] != a[i-5] || begin(il)[2] != a[i-7] || begin(il)[3] != a[i-10]) throw "wut?";
        a[i] = 1 + std::min(il);
    }
    return a;
}

int main() {
    // Change constexpr to const make gcc returns expected result
    constexpr auto bottle_count = make_bottle_count();

    std::cout << bottle_count[17] << std::endl;   // expect 2
    std::cout << bottle_count[65] << std::endl;   // expect 7
    std::cout << bottle_count[1000] << std::endl; // expect 100
}