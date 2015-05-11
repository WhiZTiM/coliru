#include <iostream>
#include <array>

template<size_t N>
using dice=std::array<unsigned char, N>;

template<size_t N>
unsigned end_die_size(dice<N> const& d) {
    unsigned r = 6;
    for (auto const& x : d) {
        int i = &x-d.data();
        int power = N-i;
        
        for (int i = 0; i < power; ++i) {
            r *= x;
        }
    }
    return r;
}
template<size_t N>
bool inc(dice<N>& d) {
    for (auto& x:d) {
        if (x == 6) {
            x = 1;
            continue;
        }
        ++x;
        return true;
    }
    return false;
}
template<size_t N>
dice<N> init() {
    dice<N> r;
    for (auto& x:r)
        x = 1;
    return r;
}
template<size_t N>
unsigned total_end_die_size() {
    auto d = init<N>();
    unsigned r = 0;
    do {
        r += end_die_size<N>(d);
    } while( inc(d) );
    return r;
}
template<size_t N>
unsigned count() {
    unsigned r = 1;
    for (int i = 0; i < N; ++i)
        r*=6;
    return r;
}
unsigned total_result() {
    unsigned r = 0;
    r += total_end_die_size<1>();
    r += total_end_die_size<2>();
    r += total_end_die_size<3>();
    r += total_end_die_size<4>();
    r += total_end_die_size<5>();
    r += total_end_die_size<6>();
    return r;
}
unsigned total_count() {
    unsigned r = 0;
    r += count<1>();
    r += count<2>();
    r += count<3>();
    r += count<4>();
    r += count<5>();
    r += count<6>();
    return r;
}
double average_result() {
    return total_result()/double(total_count());
}
int main()
{
    std::cout << average_result() + 0.5 << '\n';
}