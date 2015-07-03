#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <array>

namespace util {

template<typename IntegerT, IntegerT... Ns>
struct integer_sequence
{
    static_assert(std::is_integral<IntegerT>::value, "util::integer_sequence can only be instantiated with an integral type");

    using type = integer_sequence;
    using value_type = IntegerT;

    static constexpr std::size_t size() noexcept
    {
        return sizeof...(Ns);
    }
};

namespace detail {

template<typename, typename>
struct append_incremented_sequence;

template<std::int_fast32_t... Ns1, std::int_fast32_t... Ns2>
struct append_incremented_sequence<integer_sequence<std::int_fast32_t, Ns1...>, integer_sequence<std::int_fast32_t, Ns2...>>
  : integer_sequence<std::int_fast32_t, Ns1..., (sizeof...(Ns1) + Ns2)...>
{ };

template<std::int_fast32_t>
struct generate_integer_sequence;

template<std::int_fast32_t N>
struct generate_integer_sequence final : append_incremented_sequence<
    typename generate_integer_sequence<N / 2>::type,
    typename generate_integer_sequence<N - N / 2>::type
>
{ };

template<>
struct generate_integer_sequence<0> final : integer_sequence<std::int_fast32_t>
{ };

template<>
struct generate_integer_sequence<1> final : integer_sequence<std::int_fast32_t, 0>
{ };

template<typename, typename>
struct cast_integer_sequence;

template<typename T, std::int_fast32_t... I>
struct cast_integer_sequence<T, integer_sequence<std::int_fast32_t, I...>> final : integer_sequence<T, I...>
{ };

template<typename T, T CountN>
struct make_integer_sequence final
{
    static_assert(std::is_integral<T>::value, "util::make_integer_sequence can only be instantiated with an integral type");
    static_assert(CountN >= 0, "util::make_integer_sequence input shall not be negative");

    using type = typename cast_integer_sequence<T, typename generate_integer_sequence<CountN>::type>::type;
};

} // namespace detail

template<typename T, T CountN>
using make_integer_sequence = typename detail::make_integer_sequence<T, CountN>::type;

} // namespace util
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

constexpr std::size_t SQUARE_COUNT = 496;
namespace IMPL_NS = std;

template<typename T, T... Ns>
inline constexpr std::array<T, sizeof...(Ns)> make_squares_impl(IMPL_NS::integer_sequence<T, Ns...>) noexcept
{
    return {{ (Ns * Ns)... }};
}

template<typename T, std::size_t SizeN>
inline constexpr std::array<T, SizeN> make_squares() noexcept
{
    return make_squares_impl<T>(IMPL_NS::make_integer_sequence<T, SizeN>{});
}

auto const squares = make_squares<unsigned, SQUARE_COUNT>(); // compiler bug, this should be constexpr :-[

int main()
{
    for (unsigned i{}; i != 20; ++i)
        std::cout << i << ":\t" << squares[i] << '\n';
}
