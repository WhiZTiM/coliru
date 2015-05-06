#include <chrono>
#include <thread>

using namespace std::literals;

int main() {
    for (auto i = 0; i < 10000; ++i) {
        std::thread([] {
            std::this_thread::sleep_for(10s);
        }).detach();
    }
    std::this_thread::sleep_for(10s);
    return 0;
}