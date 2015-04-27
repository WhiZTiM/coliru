#include <cstdint>
#include <type_traits>

enum class FooEnum : uint8_t{
    Foo1 = 0, 
    Foo2 = 1
};

constexpr uint32_t& operator|= (uint32_t& lhs, FooEnum rhs) {
    return lhs |= 1u << static_cast<uint8_t>(rhs);
}

int main() {
    uint32_t bar{0};
    constexpr auto i = bar|=FooEnum::Foo1;
}