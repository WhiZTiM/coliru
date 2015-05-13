#include <iostream>

struct Slot {
    uint32_t O : 24;
    uint8_t T;
    uint32_t L : 24;
    uint8_t S;
};
 
int main() {
    std::cout << sizeof(Slot) << std::endl;
}