#include <iostream>
#include <tbb/concurrent_queue.h>
#include <thread>

int main() {
    tbb::concurrent_bounded_queue<int> values;
    for (auto i = 0; i < 10; ++i) {
        std::thread t([&] {
            for (auto i = 0; i < 100; ++i) {
                values.push(i);
            }
        });
        t.detach();
    }
    long long result = 0;
    for (auto i = 0; i < 1000; ++i) {
        int value;
        values.pop(value);
        result += value;
    }
    std::cout << result << '\n';
    return 0;
}