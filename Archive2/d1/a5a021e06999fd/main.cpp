#include <iostream>
#include <cstdint>
#include <queue>
#include <vector>
#include <memory>

struct before {
    int32_t f1;
    uint32_t f2;
    int* f3; // this obj has global lifetime in a static array, can use offset in static array instead of pointer
    int f4; // enum
    int f5; // enum
    int f6; // enum
    uint32_t f7;
    int f8; // enum
    int f9; // enum
    uint32_t f10;
    uint32_t f11;
    uint32_t f12;
    uint32_t f13;
    double f14;
    int f15; // enum
    int f16; // enum
    std::queue<std::shared_ptr<int>> f17; // seems unused through the entire code base
    std::vector<std::shared_ptr<int>> f18;
    std::shared_ptr<int> f19; // shared_ptr not needed, refers to an obj in f18
    int* f20; // this obj has global lifetime in a static array, can use offset in static array instead of pointer
};

struct after {
    std::vector<std::shared_ptr<int>> f18;
    
    double f14;
    
    int32_t f1;
    uint32_t f2;
    int f3; // this obj has global lifetime in a static array, can use offset in static array instead of pointer
    uint32_t f7;
    uint32_t f10;
    uint32_t f11;
    uint32_t f12;
    uint32_t f13;
    int f19; // shared_ptr not needed, refers to an obj in f18
    int f20; // this obj has global lifetime in a static array, can use offset in static array instead of pointer

    char f8; // enum
    char f9; // enum
    char f4; // enum
    char f5; // enum
    char f6; // enum
    char f15; // enum
    char f16; // enum
};

int main() {
    std::cout
        << "before: " << sizeof(before) << std::endl 
        << "after: " << sizeof(after) << std::endl;
}