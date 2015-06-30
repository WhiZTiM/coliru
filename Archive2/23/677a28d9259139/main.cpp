#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
 
class b1 {
    public:
    void bogus() {
        std::cout << "b1" << std::endl;
    }
};

class b2 {
    public:
    void bogus() {
        std::cout << "b2" << std::endl;
    }
};

class a : public b1, public b2 {
    public:
    a() {
        std::cout << "a" << std::endl;
    }
    void bogus() {
        std::cout << "call b1" << std::endl;
        b1::bogus();
        std::cout << "call b2" << std::endl;
        b2::bogus();
    }
};
 
int main()
{
    a A;
    A.bogus(); // ?
}