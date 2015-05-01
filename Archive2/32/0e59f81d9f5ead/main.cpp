#include <iostream>
#include <algorithm>
#include <string>

std::string caesar_encode(const std::string& input, std::size_t key)
{
    std::string result;
    std::transform(
        input.begin(), input.end(),
        std::back_inserter(result),
        [&](const char c) { return c + key; }
    );
    return result;
}

std::string caesar_decode(const std::string& input, std::size_t key)
{
    std::string result;
    std::transform(
        input.begin(), input.end(),
        std::back_inserter(result),
        [&](const char c) { return c - key; }
    );
    return result;
}

int main()
{
    std::string test("Julius Caesar");
    auto encoded = caesar_encode(test, 123);
    auto decoded = caesar_decode(encoded, 123);
    std::cout <<  test << " -> " << encoded << " -> " << decoded << std::endl;
    return 0;
}