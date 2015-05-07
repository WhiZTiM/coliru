#include <cstdint>
#include <iostream>

enum TestEnum : uint8_t
{
    test_value = 0x01,   
};

int main()
{
    TestEnum next = test_value + 1;
}
