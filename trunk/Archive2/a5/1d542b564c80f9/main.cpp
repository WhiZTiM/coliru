#include <algorithm>
#include <random>
#include <iostream>

static const char allowed_values[] =
    "0123456789"
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "+/";
static const size_t char_count = sizeof(allowed_values) - 1;
    
class TokenCharacterDistribution
{
public:
    typedef char result_type;

    template<typename Generator>
    result_type operator()(Generator& r)
    {
        return allowed_values[allowed(r)];
    }

private:
    std::uniform_int_distribution<size_t> allowed = std::uniform_int_distribution<size_t>(0, char_count - 1);
};

int main()
{
    std::random_device rng;
    TokenCharacterDistribution d;
    for (size_t i = 0; i < 128; ++i)
    {
        std::cout << d(rng);
    }
    std::cout << '\n';
    return 0;
}
