#include <type_traits>
#include <iostream>
#include <cstdint>
#include <string>
#include <algorithm>

template<typename T, std::size_t Size>
struct bitsection
{
    static std::size_t const size = Size;
    typedef T type;
};

template<std::size_t Bytes, typename... Sections>
class bitfield
{
private:

    unsigned char buffer[Bytes] = {};

    template<std::size_t Index, typename Section, typename... Rest>
    struct section_at
    {
        typedef typename section_at<Index - 1, Rest...>::section section;
    };

    template<typename Section, typename... Rest>
    struct section_at < 0, Section, Rest... >
    {
        typedef Section section;
    };

    template<std::size_t Index, typename Section, typename... Rest>
    struct offset_at
    {
        static std::size_t const value = offset_at<Index - 1, Section, Rest...>::value + section_at<Index - 1, Section, Rest...>::section::size;
    };

    template<typename Section, typename... Rest>
    struct offset_at < 0, Section, Rest... >
    {
        static std::size_t const value = 0;
    };

public:

    static_assert(offset_at<sizeof...(Sections), Sections..., void>::value <= 8 * Bytes, "Provided bit sections exceed available space.");

    bitfield()
    {}

    // Copy
    template<typename C>
    bitfield(C const& other)
        : bitfield(other.begin(), other.end())
    {}

    //template<std::size_t N, typename... Args>
    //bitfield(bitfield<N, Args...> const& other)
    //    : bitfield(other.begin(), other.end())
    //{}

    template<std::size_t N>
    bitfield(char(&other)[N])
        : bitfield(other, other + N)
    {}

    template<std::size_t N>
    bitfield(unsigned char(&other)[N])
        : bitfield(other, other + N)
    {}

    template<typename In>
    bitfield(In start, In end)
    {
        static_assert(sizeof(*start) == 1, "Invalid range constructor. Underlying iterator type needs to be char or unsigned char.");

        std::copy(start, end, buffer);
    }

    template<std::size_t Index, typename R>
    void set(R value)
    {
        static_assert(Index < sizeof...(Sections), "Index out of bit field range.");

        auto const offset = offset_at<Index, Sections...>::value;
        auto const shift = offset % 8;
        typedef typename section_at<Index, Sections...>::section section;

        std::uint64_t copy = 0;
        std::copy_n(buffer + offset / 8, ((section::size + 7) & ~7) / 8, reinterpret_cast<unsigned char*>(&copy));
        copy &= ~(((1 << section::size) - 1) << shift);
        copy |= (value & ((1 << section::size) - 1)) << shift;
        std::copy_n(reinterpret_cast<unsigned char*>(&copy), ((shift + section::size + 7) & ~7) / 8, buffer + offset / 8);
    }

    template<std::size_t Index>
    typename section_at<Index, Sections...>::section::type get()
    {
        static_assert(Index < sizeof...(Sections), "Index out of bit field range.");

        auto const offset = offset_at<Index, Sections...>::value;
        auto const shift = offset % 8;
        typedef typename section_at<Index, Sections...>::section section;

        std::uint64_t copy = 0;
        std::copy_n(buffer + offset / 8, ((shift + section::size + 7) & ~7) / 8, reinterpret_cast<unsigned char*>(&copy));

        return (typename section::type)((copy >> shift) & ((1 << section::size) - 1));
    }

    std::size_t size() const
    {
        return Bytes;
    }

    unsigned char* data()
    {
        return buffer;
    }

    unsigned char* begin()
    {
        return buffer;
    }

    unsigned char* end()
    {
        return buffer + size();
    }

    unsigned char const* cbegin() const
    {
        return buffer;
    }

    unsigned char const* cend() const
    {
        return buffer + size();
    }
};

int main()
{
    bitfield<7,
        bitsection<bool, 1>,
        bitsection<int, 4>,
        bitsection<unsigned short, 6>,
        bitsection<int, 5>,
        bitsection<char, 8>
    > y;                //             00 00 00
    y.set<0>(true);     // 01 00 00 -> 01 00 00
    y.set<1>(3);        // 06 00 00 -> 07 00 00
    y.set<2>(8);        // 00 01 00 -> 07 01 00
    y.set<3>(0xFFFF);   // 00 F8 00 -> 07 F9 00 caps at 6 bits
    y.set<4>('A');      // 00 F8 41 -> 07 F9 41

    std::cout << y.get<0>() << " " << y.get<1>() << " " << y.get<2>() << " " << y.get<3>() << " " << y.get<4>() << std::endl;

    auto x = y;

    std::cout << "Size: " << y.size();
    std::cout << ", Contents: ";
    for (auto const& byte : y)
    {
        std::cout.width(2);
        std::cout.fill('0');
        std::cout << std::hex << std::uppercase << std::right;
        std::cout << (unsigned int)(byte) << " ";
    }
    std::cout << std::endl;

    std::cout << "Size: " << x.size();
    std::cout << ", Contents: ";
    for (auto const& byte : x)
    {
        std::cout.width(2);
        std::cout.fill('0');
        std::cout << std::hex << std::uppercase << std::right;
        std::cout << (unsigned int)(byte) << " ";
    }
    std::cout << std::endl;
    return 0;
}
