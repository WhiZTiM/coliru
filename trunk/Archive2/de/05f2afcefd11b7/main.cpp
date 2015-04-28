#include <type_traits>
#include <cstdint>
#include <algorithm>

namespace marshal
{
    template<std::size_t Size, typename T = int>
    struct bitsection
    {
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
        void set(R value)
        {
            static_assert(Index < sizeof...(Sections), "Index out of bit field range.");

            auto const offset = offset_at<Index, Sections...>::value;
            auto const shift = offset % 8;
            typedef typename section_at<Index, Sections...>::section section;
            auto const byte_offset = buffer + offset / 8;
            auto const byte_length = ((shift + section::size + 7) & ~7) / 8;

            union
            {
                std::uint64_t copy = 0;
                std::array<unsigned char, byte_length> copy_array;
            };

            std::copy_n(byte_offset, byte_length, copy_array);
            copy &= ~(((1 << section::size) - 1) << shift);
            copy |= (value & ((1 << section::size) - 1)) << shift;
            std::copy_n(copy_array, byte_length, byte_offset);
        }

        template<std::size_t Index>
        typename section_at<Index, Sections...>::section::type get()
        {
            static_assert(Index < sizeof...(Sections), "Index out of bit field range.");

            auto const offset = offset_at<Index, Sections...>::value;
            auto const shift = offset % 8;
            typedef typename section_at<Index, Sections...>::section section;
            auto const byte_offset = buffer + offset / 8;
            auto const byte_length = ((shift + section::size + 7) & ~7) / 8;

            std::uint64_t copy = 0;
            std::copy_n(byte_offset, byte_length, reinterpret_cast<unsigned char*>(&copy));

            return static_cast<typename section::type>((copy >> shift) & ((1 << section::size) - 1));
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
}

#include <string>
#include <iostream>

int main()
{
    // A sample 0x062 (skill update) packet, captured from my retail character
    std::string payload {
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

    // A few enums to make prettier accessing possible
    enum CraftRanks
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

    enum CombatSkills
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
    
    enum CraftSkills
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

    enum CombatFields
    {
        CombatLevel,
        CombatCapped,
    };

    enum CraftFields
    {
        CraftRank,
        CraftLevel,
        CraftCapped,
    };

    // Because less typing
    using marshal::bitfield;
    using marshal::bitsection;

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
            bitsection<5, CraftRanks>,
            bitsection<10>,
            bitsection<1, bool>
        > craft_skills[0x0A];
        unsigned char junk2[0x0C];
    };

    // Create a sample packet based on the provided data above
    packet0x62 sample;
    std::copy(payload.begin(), payload.end(), reinterpret_cast<char*>(&sample));

    // Helper functions to print certain values
    auto print_combat = [&sample](std::string const& name, CombatSkills skill)
    {
        std::cout << name << " "
            << "level: " << sample.combat_skills[skill].get<CombatLevel>() << ", "
            << (sample.combat_skills[skill].get<CombatCapped>() ? "capped" : "uncapped") << std::endl;
    };

    auto print_craft = [&sample](std::string const& name, CraftSkills skill)
    {
        std::cout << name << " "
            << "level: " << sample.craft_skills[skill].get<CraftLevel>() << ", "
            << "rank: " << sample.craft_skills[skill].get<CraftRank>() << ", "
            << (sample.craft_skills[skill].get<CraftCapped>() ? "capped" : "uncapped") << std::endl;
    };

    // Testing
    print_combat("Hand-to-hand", HandToHand);
    print_combat("Dagger", Dagger);
    print_combat("Archery", Archery);
    print_combat("Parrying", Parrying);

    std::cout << std::endl;

    print_craft("Fishing", Fishing);
    print_craft("Woodworking", Woodworking);
    print_craft("Alchemy", Alchemy);

    std::cout << std::endl;

    // Adjusting values
    auto copy = sample.craft_skills[Woodworking];
    copy.set<CraftLevel>(50);
    copy.set<CraftCapped>(true);

    std::cout << "Woodworking (adjusted) level: " << copy.get<CraftLevel>() << ", " << (copy.get<CraftCapped>() ? "capped" : "uncapped") << std::endl;

    sample.craft_skills[Woodworking] = copy;

    // Check if it changed
    print_craft("Woodworking", Woodworking);

    std::cout << std::endl;

    return 0;
}
