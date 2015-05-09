#include <cstdint>

enum class E1 : std::uint8_t
{
    data1, data2, data3, data4,
    count, // also "invalid"
    first = data1
};

enum class E2 : std::uint64_t
{
    data1,
    data2,
    dataE1,
    dataE1End = std::uint64_t(dataE1 + std::uint8_t(E1::count)),
    data3 = dataE1End,
    count,
};

constexpr E1 fromE2(E2 e)
{
    if (E2::dataE1 <= e && e < E2::dataE1End)
        return E1(std::uint8_t(E1::first) + (std::uint64_t(e) - std::uint64_t(E2::dataE1)));
    return E1::count;
}

constexpr E2 fromE1(E1 e)
{
    if (e >= E1::count)
        return E2::count;
    return E2(std::uint64_t(E2::dataE1) + std::uint8_t(e));
}

#include <iostream>

int main()
{
    static_assert(fromE1(E1::data1) == E2::dataE1, "");
    static_assert(fromE2(E2::data3) == E1::count, "");
    static_assert(fromE2(E2::dataE1) == E1::data1, "");
}