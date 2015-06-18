#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <random>

template <class Rng, size_t N = 8>
std::string random_string(Rng& rng)
{
    std::uniform_int_distribution<char> dist('A','Z');

    std::string s;
    std::generate_n(std::back_inserter(s), N,[&](){ return dist(rng); });
    return s;
}

int main(int argc, char *argv[])
{
    int n = 0;
    if (argc == 2 && (n = atoi(argv[1])) > 0)
    {
        std::mt19937 rng(std::random_device{}());
        for (int i=1; i<=n; ++i)
            std::cout << random_string(rng) << ' ' << i << '\n';
    }
}
