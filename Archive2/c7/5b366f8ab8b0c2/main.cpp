#include <boost/interprocess/managed_mapped_file.hpp>
#include <iostream>

namespace bip = boost::interprocess;

struct MyWorker : boost::noncopyable {
    MyWorker() 
        : _shm(new bip::managed_mapped_file(bip::open_or_create, "089f8a0f-956a-441d-9b9e-e0696c43185f", 10ul<<20)) 
    {}

    ~MyWorker() {
        delete _shm;
    }
  private:
    bip::managed_mapped_file* _shm;
};

int main() {
    MyWorker instance;
}
