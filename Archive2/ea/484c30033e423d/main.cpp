#include <type_traits>
#include <cstdint>
#include <algorithm>
#include <array>
#include <iostream>

namespace marshal
{
    typedef std::uint64_t max_bit_type;

    template<std::size_t Size, typename T = int>
    struct bitsection
    {
        static_assert(sizeof(T) <= sizeof(marshal::max_bit_type), "Type size exceeds highest allowed type size.");
#if !defined(__GNUC__) || __GNUC__ > 5
        static_assert(std::is_trivially_copyable<T>::value, "The type of a bit section needs to be trivially copyable.");
#endif

        static std::size_t const size = Size;
        typedef T type;
    };

    template<std::size_t Bytes, typename... Sections>
    class bitfield
    {
    private:

        unsigned char buffer[Bytes];// = {};

        template<std::size_t Index, typename Section, typename... Rest>
        struct section_at
        {
            typedef typename section_at<Index - 1, Rest...>::section section;
        };

        template<typename Section, typename... Rest>
        struct section_at<0, Section, Rest...>
        {
            typedef Section section;
        };

        template<std::size_t Index, typename Section, typename... Rest>
        struct offset_at
        {
            static std::size_t const value = offset_at<Index - 1, Section, Rest...>::value + section_at<Index - 1, Section, Rest...>::section::size;
        };

        template<typename Section, typename... Rest>
        struct offset_at<0, Section, Rest...>
        {
            static std::size_t const value = 0;
        };

        template<std::size_t Index>
        class mirror
        {
        private:
            typedef typename section_at<Index, Sections...>::section section;
            static std::size_t const bit_offset = offset_at<Index, Sections...>::value;
            static std::size_t const bit_shift = bit_offset % 8;
            static std::size_t const byte_offset = bit_offset / 8;
            static std::size_t const byte_length = ((bit_shift + section::size + 7) & ~7) / 8;

            unsigned char* buffer;
            union
            {
                marshal::max_bit_type value;
                std::array<unsigned char, byte_length> array;
            };

            static_assert(Index < sizeof...(Sections), "Index out of bit field range.");
            static_assert(byte_length <= sizeof(marshal::max_bit_type), "Invalid type with size larger than the maximum allowed.");

        public:
            mirror(unsigned char* original)
                : buffer{original + byte_offset}, value{0}
            {
            }

            typename section::type operator =(typename section::type const& other)
            {
                std::copy_n(buffer, byte_length, array.data());
                value &= ~(((1 << section::size) - 1) << bit_shift);
                value |= (other & ((1 << section::size) - 1)) << bit_shift;
                std::copy_n(array.data(), byte_length, buffer);
                return other;
            }

            operator typename section::type()
            {
                std::copy_n(buffer, byte_length, array.data());
                return static_cast<typename section::type>((value >> bit_shift) & ((1 << section::size) - 1));
            }
        };

    public:

        static_assert(offset_at<sizeof...(Sections), Sections..., void>::value <= 8 * Bytes, "Provided bit sections exceed available space.");

        bitfield()
        {}

        template<typename C>
        bitfield(C const& cont)
            : bitfield(cont.begin(), cont.end())
        {}

        template<std::size_t N>
        bitfield(char(&other)[N])
            : bitfield(other, other + N)
        {}

        template<std::size_t N>
        bitfield(unsigned char(&other)[N])
            : bitfield(other, other + N)
        {}

        template<typename It>
        bitfield(It const& start, It const& end)
        {
            static_assert(sizeof(*start) == 1, "Invalid range constructor. Underlying iterator type needs to be char or unsigned char.");

            std::copy(start, end, buffer);
        }

        template<std::size_t Index, typename R>
        typename section_at<Index, Sections...>::section::type set(R value)
        {
            return mirror<Index>{buffer} = value;
        }

        template<std::size_t Index>
        typename section_at<Index, Sections...>::section::type get()
        {
            return mirror<Index>(buffer);
        }

        std::size_t size() const
        {
            return Bytes;
        }

        unsigned char* data()
        {
            return buffer;
        }
    };

    template<std::size_t Index, std::size_t Bytes, typename... Sections>
    auto set(bitfield<Bytes, Sections...> bf) -> decltype(bf.set<Index>())
    {
        return bf.template set<Index>();
    }

    template<std::size_t Index, std::size_t Bytes, typename... Sections>
    auto get(bitfield<Bytes, Sections...> bf) -> decltype(bf.get<Index>())
    {
        return bf.template get<Index>();
    }
}

#include <string>
#include <iostream>

// A few enums to make prettier accessing possible
namespace Combat
{
    namespace Fields
    {
        enum Field
        {
            Level,
            Capped,
        };
    }

    namespace Skills
    {
        enum Skill
        {
            None,
            HandToHand,
            Dagger,
            Sword,
            GreatSword,
            Axe,
            GreatAxe,
            Scythe,
            Polearm,
            Katana,
            GreatKatana,
            Club,
            Staff,
            _Combat13,
            _Combat14,
            _Combat15,
            _Combat16,
            _Combat17,
            _Combat18,
            _Combat19,
            _Combat20,
            _Combat21,
            AutomatonMelee,
            AutomatonArchery,
            AutomatonMagic,
            Archery,
            Marksmanship,
            Throwing,
            Guard,
            Evasion,
            Shield,
            Parrying,
            DivineMagic,
            HealingMagic,
            EnhancingMagic,
            EnfeeblingMagic,
            ElementalMagic,
            DarkMagic,
            SummoningMagic,
            Ninjutsu,
            Singing,
            StringedInstrument,
            WindInstrument,
            BlueMagic,
            Geomancy,
            Handbell,
            _Magic46,
            _Magic47,
        };
    }
}

namespace Craft
{
    namespace Fields
    {
        enum Field
        {
            Rank,
            Level,
            Capped,
        };
    }

    namespace Skills
    {
        enum Skill
        {
            Fishing,
            Woodworking,
            Smithing,
            Goldsmithing,
            Clothcraft,
            Leathercraft,
            Bonecraft,
            Alchemy,
            Cooking,
            Synergy,
        };
    }

    namespace Ranks
    {
        enum Rank
        {
            Amateur,
            Recruit,
            Novice,
            Initiate,
            Apprentice,
            Journeyman,
            Craftsman,
            Artisan,
            Adept,
            Veteran,
            Expert,
        };
    }
}

int main()
{
    // A sample 0x062 (skill update) packet, captured from my retail character
    std::string payload{
        '\x62', '\x80', '\x06', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\x00', '\x00', '\x2C', '\x81', '\xB8', '\x81', '\x5E', '\x81', '\x90', '\x80', '\x96', '\x80', '\xA6', '\x80', '\x90', '\x80',
        '\x90', '\x80', '\x00', '\x80', '\x00', '\x80', '\x2C', '\x81', '\x90', '\x80', '\x00', '\x80', '\x00', '\x80', '\x00', '\x80',
        '\x00', '\x80', '\x00', '\x80', '\x00', '\x80', '\x00', '\x80', '\x00', '\x80', '\x00', '\x80', '\x00', '\x80', '\x00', '\x80',
        '\x00', '\x80', '\x70', '\x81', '\x7A', '\x81', '\x4E', '\x81', '\x0A', '\x80', '\xB2', '\x81', '\x1B', '\x81', '\xA0', '\x02',
        '\x00', '\x80', '\x00', '\x80', '\x10', '\x80', '\x10', '\x80', '\x0A', '\x80', '\x00', '\x80', '\x10', '\x80', '\x00', '\x80',
        '\x00', '\x80', '\x05', '\x80', '\x05', '\x80', '\x00', '\x80', '\x00', '\x80', '\x00', '\x80', '\x00', '\x80', '\x00', '\x80',
        '\x03', '\x04', '\xA4', '\x05', '\xE0', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x20', '\x00', '\xA2', '\x03',
        '\x61', '\x01', '\x00', '\x00', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF',
    };

    // Because less typing
    using marshal::bitfield;
    using marshal::bitsection;
    using marshal::get;
    //using marshal::set;

    // The actual class definition
    struct packet0x62
    {
        unsigned int header;
        unsigned char junk1[0x7C];
        bitfield<2,
            bitsection<15>,
            bitsection<1, bool>
        > combat_skills[0x30];
        bitfield<2,
            bitsection<5, Craft::Ranks::Rank>,
            bitsection<10>,
            bitsection<1, bool>
        > craft_skills[0x0A];
        unsigned char junk2[0x0C];
    };

    // Create a sample packet based on the provided data above
    packet0x62 sample;
    std::copy(payload.begin(), payload.end(), reinterpret_cast<char*>(&sample));

    // Helper functions to print certain values
    auto print_combat = [&sample](std::string const& name, Combat::Skills::Skill skill)
    {
        std::cout << name << " "
            << "level: " << sample.combat_skills[skill].get<Combat::Fields::Level>() << ", "
            << (sample.combat_skills[skill].get<Combat::Fields::Capped>() ? "capped" : "uncapped") << std::endl;
    };

    auto print_craft = [&sample](std::string const& name, Craft::Skills::Skill skill)
    {
        std::cout << name << " "
            << "level: " << sample.craft_skills[skill].get<Craft::Fields::Level>() << ", "
            << "rank: " << sample.craft_skills[skill].get<Craft::Fields::Rank>() << ", "
            << (sample.craft_skills[skill].get<Craft::Fields::Capped>() ? "capped" : "uncapped") << std::endl;
    };

    // Testing
    print_combat("Hand-to-hand", Combat::Skills::HandToHand);
    print_combat("Dagger", Combat::Skills::Dagger);
    print_combat("Archery", Combat::Skills::Archery);
    print_combat("Parrying", Combat::Skills::Parrying);

    std::cout << std::endl;

    print_craft("Fishing", Craft::Skills::Fishing);
    print_craft("Woodworking", Craft::Skills::Woodworking);
    print_craft("Alchemy", Craft::Skills::Alchemy);

    std::cout << std::endl;

    // Adjusting values
    auto copy = sample.craft_skills[Craft::Skills::Woodworking];
    copy.set<Craft::Fields::Level>(50);
    copy.set<Craft::Fields::Capped>(true);

    std::cout << "Woodworking set to: " << copy.get<Craft::Fields::Level>() << ", " << (copy.get<Craft::Fields::Capped>() ? "capped" : "uncapped") << std::endl;

    sample.craft_skills[Craft::Skills::Woodworking] = copy;

    // Check if it changed
    print_craft("Woodworking", Craft::Skills::Woodworking);

    std::cout << std::endl;

    return 0;
}
