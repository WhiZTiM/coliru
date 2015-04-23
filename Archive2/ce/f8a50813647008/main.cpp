#include <iostream>
#include <sys/mman.h>

int main() {
    auto buf = static_cast<unsigned char*>(mmap(nullptr, 64, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0));
    buf[0] = 0x0f;
    buf[1] = 0xaf;
    buf[2] = 0xff;
    buf[3] = 0x89;
    buf[4] = 0xf8;
    buf[5] = 0xc3;
    auto square = reinterpret_cast<int(*)(int)>(buf);
    for (auto i = 0; i < 10; ++i) {
        std::cout << square(i) << '\n';
    }
    return 0;
}