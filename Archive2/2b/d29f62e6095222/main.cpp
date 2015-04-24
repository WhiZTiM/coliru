#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>

namespace bip = boost::interprocess;

struct MyWorker : boost::noncopyable {
    MyWorker() 
    try : _shm(new bip::managed_shared_memory(bip::open_or_create, "089f8a0f-956a-441d-9b9e-e0696c43185f", 10ul<<20)) 
    {
        // empty constructor body
    } catch (...) 
    { std::cout << "Look ma! I'm handling my exceptions\n" << "\n";
    }

    ~MyWorker() {
        delete _shm;
    }
  private:
    bip::managed_shared_memory* _shm;
};

int main() {
    MyWorker instance;
}
