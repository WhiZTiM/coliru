#include <cstdint>
#include <type_traits>

enum class FooEnum : uint8_t{
    Foo1 = 0, 
    Foo2 = 1
};

constexpr uint32_t& operator|= (uint32_t& lhs, FooEnum rhs) {
    return lhs |= 1u << static_cast<uint8_t>(rhs);
}

constexpr uint32_t foo(FooEnum rhs)
{
    uint32_t x = 0;
    x |= rhs;
    return x;
}

int main() {
    constexpr auto r = foo(FooEnum::Foo2);
}