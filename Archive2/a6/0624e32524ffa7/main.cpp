#include <iostream>
#include <string>

typedef struct
{
    unsigned boolFoo  : 1;
    unsigned pLACEHOLDER : 7;
} __attribute__((packed, aligned(1))) KnownBitFlags1_t;

int main()
{
    std::cout <<sizeof(KnownBitFlags1_t);
}