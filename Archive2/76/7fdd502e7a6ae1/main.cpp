#include <type_traits>
#include <cstdint>

template<typename> struct is_bitmask : std::false_type {};

template<typename E>
constexpr typename std::enable_if<is_bitmask<E>::value, E>::type operator|( const E lhs, const E rhs )
{
    using UT = typename std::underlying_type<E>::type;
    return E(UT(lhs) | UT(rhs));
}

enum class gpiopin : std::uint32_t {
    p0 = 0x00000001,
    // ...
    p14 = 0x00004000,
    p15 = 0x00008000
};
// register the type for the above operator|
template<> struct is_bitmask<gpiopin> : std::true_type {};

int main()
{
    static_assert( ( gpiopin::p0 | gpiopin::p14 ) == gpiopin(0x00004001), "Oops" );
}
