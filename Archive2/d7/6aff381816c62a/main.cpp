#include <iostream>
#include <thread>

int main() {
    auto f = []() -> void {
        for (auto& i : {0,1,2,3,4,5,6,7,8,9}) {
            std::cout << i << std::endl;
        }
        };
    std::thread t1(f);
    std::thread t2(f);
    t1.join();
    t2.join();
    return 0;
}