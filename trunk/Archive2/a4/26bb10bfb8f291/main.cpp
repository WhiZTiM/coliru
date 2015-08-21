#include <iostream>
#include <thread>
#include <functional>

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
    F foo;
    std::thread t(&F::operator(), &foo);
    foo.stopIt();
}