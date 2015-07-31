#include <type_traits>

namespace
{

struct A { int i; };

volatile A a{};
static_assert(std::is_volatile< decltype(a) >{}, "1");
static_assert(std::is_volatile< decltype(a.i) >{}, "2");

}
