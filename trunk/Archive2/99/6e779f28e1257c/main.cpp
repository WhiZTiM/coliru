// =================
//       DATA
// =================

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
    data6,
    data7,
#endif
    count, // also "invalid"
    first = data1
};

enum class E11 : std::uint8_t
{
    data1, data2, data3,
#ifdef CHANGED
    data4,
    data5,
#endif
    count,
    first = data1
};

enum class E2 : std::uint64_t
{
    data1,
    data2,
    data3,
    data3End = data3 + int_t(E1::count),
    data4 = data3End,
    data5,
    data6,
    data6End = data6 + int_t(E11::count),
    data7,
    count
};

// =================
//       CODE
// =================

#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

auto const& unstableRangeEnds()
{
    // extend if E2 gets more unstable ranges
    static E2 const array[] = 
    {
        E2::data3End,
        E2::data6End,
    };
    return array;
}

std::string serialise(E2 e)
{
    std::ostringstream output;
    
    E2 const* p_end = nullptr;
    for (auto const& end : unstableRangeEnds())
    {
        if (e >= end)
            p_end = &end;
    }
    
    if (p_end != nullptr)
    {
        output << (p_end - &unstableRangeEnds()[0]) << " ";
        output << std::to_string(int_t(*p_end));
    }
    else
        output << "-1 -1";
            
    output << " " << std::to_string(int_t(e));
    return output.str();
}

E2 deserialiseE2(std::string const& data)
{
    std::istringstream input(data);
    
    std::int64_t endIndex, oldEnd;
    std::uint64_t value;
    input >> endIndex >> oldEnd >> value;
    
    std::int64_t offset = 0;
    if (endIndex != -1 && oldEnd != -1)
    {
        auto const newEnd = int_t(unstableRangeEnds()[endIndex]);
        offset = newEnd - oldEnd;
    }
    return E2(value + offset);
}

// =================
//       TEST
// =================

#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>

int main()
{
    E2 const expected[] = 
    {
        E2(int_t(E2::data3) + int_t(E1::data2)),
        E2::data5,
        E2::data7,
    };
    auto const fname = "test.data";
    
    for (auto const& end : unstableRangeEnds())
    {
        std::cout << "end " << (&end - std::begin(unstableRangeEnds())) << ": " << int_t(end) << std::endl;
    }

#ifndef CHANGED
    // serialise
    std::ofstream file(fname, std::ios::trunc);
    for (auto ex : expected)
        file << serialise(ex) << "\n";
#else
    // deserialise with changes to source enums
    std::ifstream file(fname);
    std::string data;
    for (auto ex : expected)
    {
        std::getline(file, data);
        std::cout << std::quoted(data) << ": " << int_t(ex) << std::endl;
        assert(deserialiseE2(data) == ex);
    }
#endif
}