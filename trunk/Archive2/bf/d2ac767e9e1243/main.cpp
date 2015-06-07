#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <thread>

int main()
{
    std::thread t1([](){ std::cout << "lolz\n"; });
    t1.join();
    std::thread t2([](){ std::cout << "lmao\n"; });
    t2.join();
}
