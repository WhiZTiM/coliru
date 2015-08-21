#include <type_traits>

int const ci = 20;
decltype(auto) i = ci;

static_assert ( std::is_same< decltype(ci), decltype(i) >::value, "not same" );
static_assert ( ! std::is_same< decltype(i), int >::value, "not const" );
