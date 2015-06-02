#include <functional>
#include <cstdint>

int main()
{
    auto x = std::plus<std::int32_t>()(std::int32_t(2), std::int32_t(3));
}
