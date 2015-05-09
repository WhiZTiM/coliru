#include <cstdint>

enum class E1 : std::uint8_t
{
    data1, data2, data3, data4,
#ifdef CHANGED
    data5,
#endif
    count, // also "invalid"
    first = data1
};

enum class E2 : std::uint64_t
{
    data1,
    data2,
    data3,
    data3End = std::uint64_t(data3 + std::uint8_t(E1::count)),
    data4 = data3End,
    data5,
    count
};

constexpr E1 fromE2(E2 e)
{
    if (E2::data3 <= e && e < E2::data3End)
        return E1(std::uint8_t(E1::first) + (std::uint64_t(e) - std::uint64_t(E2::data3)));
    return E1::count;
}

constexpr E2 fromE1(E1 e)
{
    if (e >= E1::count)
        return E2::count;
    return E2(std::uint64_t(E2::data3) + std::uint8_t(e));
}

static_assert(fromE1(E1::data1) == E2::data3, "");
static_assert(fromE2(E2::data4) == E1::count, "");
static_assert(fromE2(E2::data3) == E1::data1, "");

#include <cassert>
#include <string>
#include <fstream>

std::string serialise(E2 e)
{
    // todo
    return "";
}

E2 deserialiseE2(std::string const& data)
{
    // todo
    return E2::count;
}

int main()
{
    auto const expected1 = E2(std::uint64_t(E2::data3) + std::uint8_t(E1::data2));
    auto const expected2 = E2::data5;

    std::fstream file("test.data", std::ios::in | std::ios::out);
#ifndef CHANGED
    // serialise
    file << serialise(expected1) << "\n";
    file << serialise(expected2) << "\n";
#else
    // deserialise with changes to source enums
    std::string data;
    std::getline(file, data);
    assert(deserialiseE2(data) == expected1);
    std::getline(file, data);
    assert(deserialiseE2(data) == expected2);
#endif
}