#include <iostream>
#include <thread>
#include <functional>
#include <chrono>

class F
{
    bool proceed;
public:
    F():proceed(true) {}
    void operator()() 
    {
        while(proceed) {std::cout<<".";}
        std::cout<<"stopped\n";
    }
    void stopIt() {proceed=false;}
};

int main()
{
    using namespace std::literals;
    F foo;
    std::thread t(std::ref(foo));
    std::this_thread::sleep_for(1ms);
    foo.stopIt();
    t.join();
}