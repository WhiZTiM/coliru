#include <type_traits>

namespace
{

struct A { int i; };

const A b{};
static_assert(std::is_const< decltype(b) >{});
static_assert(std::is_const< decltype(b.i) >{});

}
