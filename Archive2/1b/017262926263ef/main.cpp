#include <iostream>
#include <chrono>

int main() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto s = (duration_cast<milliseconds>(now.time_since_epoch()).count() % 60000) / 1000.;
    std::cout << s << std::endl;
}