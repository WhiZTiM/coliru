#include <vector>
#include <iostream>
#include <cstdint>
#include <random>
#include <string>
#include <algorithm>

std::vector<uint8_t> GenerateSalt()
{
    const size_t salt_length = 128;
    // use all printable ascii characters for salt
    const char salt_value_minimum = '!';
    const char salt_value_maximum = '~';

    std::uniform_int_distribution<char> valid_characters(salt_value_minimum,
                                                         salt_value_maximum);
    std::random_device rng;

    std::vector<uint8_t> result(salt_length);
    std::generate(result.begin(), result.end(), [&]() -> uint8_t
    {
        return valid_characters(rng);
    });

    return result;
}

int main()
{
    std::vector<uint8_t> slt = GenerateSalt();
    std::cout << std::string(slt.begin(), slt.end()) << std::endl;
    return 0;
}
