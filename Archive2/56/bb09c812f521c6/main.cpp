#include <iostream>
#include <type_traits>

template <typename T>
decltype(sizeof(T), std::true_type{}) is_complete_impl(int);

template <typename T>
std::false_type is_complete_impl(...);

// This traits is UB even if it seems to work
template <typename T>
using is_complete = decltype(is_complete_impl<T>(0));

class B{};
class C;

static_assert(is_complete<B>::value, "");
static_assert(!is_complete<C>::value, "");

class C {};

//static_assert(is_complete<C>::value, ""); // already instanstiate with false value


int main() {
}