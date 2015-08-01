#include <array>

constexpr auto make_array(int i)
{
    std::array<int, 2> a{ i, 0 };
    return a;
}

constexpr auto arr = make_array(1);

static_assert(arr[0] == 1, "");