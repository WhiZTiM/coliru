#include <array>

constexpr auto make_array(int i)
{
    return std::array<int, 2>{ i, 0 };
}

constexpr auto arr = make_array(1);

static_assert(arr[0] == 1, "");