#include <cstdint>
#include <iostream>

enum TestEnum : uint8_t
{
    test_value = 0x01,   
};

void f1(TestEnum enum_)
{
    std::cout << enum_ << std::endl;
}

int main()
{
    f1(TestEnum::test_value);
    f1(1);
}