#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    std::thread t2([](){ std::cout << "Hello Thread!"; });
    std::thread t3([](){ std::cout << "Hello Thread!"; });
    t.join();
    t2.join();
    t3.join();
}