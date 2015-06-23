#include <cstdint>
#include <array>


struct Key
{
    uint64_t members[4];
};


using F = std::array<int, 4>;


uint64_t hash(Key key)
{
    uint64_t result = 0;
    result ^= (key.members[0] % f[0]) * f[0];
    result ^= (key.members[1] % f[1]) * f[1];
    result ^= (key.members[2] % f[2]) * f[2];
    result ^= (key.members[3] % f[3]) * f[3];
    return result;
}


std::array<int, 4> f = { 1, 1, 1, 1 };
std::vector<Key> keys;

void addKey(Key key)
{
    
}


int main()
{
}