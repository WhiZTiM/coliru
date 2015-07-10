#include <type_traits>
#include <cstdint>

template<typename E, E... I>
struct mask_or;

template<typename E>
struct mask_or<E> {
    static constexpr E value = E(0);
};

template<typename E, E first, E... rest>
struct mask_or<E, first, rest...> {
    using UT = typename std::underlying_type<E>::type;
    static constexpr E value = E(UT(first) | UT(mask_or<E, rest...>::value));
};

enum class gpiopin : std::uint32_t {
    p0 = 0x00000001,
    // ...
    p14 = 0x00004000,
    p15 = 0x00008000
};

int main()
{
    static_assert( mask_or<gpiopin, gpiopin::p0, gpiopin::p14>::value == gpiopin(0x00004001), "Oops" );
}
