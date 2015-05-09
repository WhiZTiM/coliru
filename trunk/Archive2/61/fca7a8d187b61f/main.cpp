#include <cstdint>
#include <type_traits>

template<class E>
constexpr std::underlying_type_t<E> int_t(E v)
{
    return std::underlying_type_t<E>(v);
}

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
        return E1(int_t(E1::first) + (int_t(e) - int_t(E2::data3)));
    return E1::count;
}

constexpr E2 fromE1(E1 e)
{
    if (e >= E1::count)
        return E2::count;
    return E2(int_t(E2::data3) + int_t(e));
}

static_assert(fromE1(E1::data1) == E2::data3, "");
static_assert(fromE2(E2::data4) == E1::count, "");
static_assert(fromE2(E2::data3) == E1::data1, "");

#include <cassert>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

std::string serialise(E2 e)
{
    return std::to_string(int_t(e));
}

E2 deserialiseE2(std::string const& data)
{
    return E2(std::stol(data));
}

int main()
{
    auto const expected1 = E2(int_t(E2::data3) + int_t(E1::data2));
    auto const expected2 = E2::data5;
    auto const fname = "test.data";

#ifndef CHANGED
    // serialise
    std::ofstream file(fname, std::ios::out | std::ios::trunc);
    file << serialise(expected1) << "\n";
    file << serialise(expected2) << "\n";
#else
    // deserialise with changes to source enums
    std::ifstream file(fname);
    std::string data;
    std::getline(file, data);
    std::cout << std::quoted(data) << ": " << int_t(expected1) << std::endl;
    assert(deserialiseE2(data) == expected1);
    std::getline(file, data);
    std::cout << std::quoted(data) << ": " << int_t(expected2) << std::endl;
    assert(deserialiseE2(data) == expected2);
#endif
}