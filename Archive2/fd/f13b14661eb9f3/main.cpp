#include <chrono>

struct Foo
{
    std::chrono::high_resolution_clock::time_point gameStartClock = std::chrono::high_resolution_clock::now();
};

int main() {}
