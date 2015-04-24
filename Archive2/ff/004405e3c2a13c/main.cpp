#include <boost/interprocess/managed_mapped_file.hpp>
#include <iostream>

namespace bip = boost::interprocess;

struct MyWorker : boost::noncopyable {
    MyWorker() : _shm(init_shm()) { }  
  private:
    static bip::managed_mapped_file init_shm() {
        try {
            return bip::managed_mapped_file(bip::open_or_create, "/no-permission", 10ul<<20);
        } catch(...) {
            std::cout << "Look ma! I'm handling my exceptions\n" << "\n";
            // try smaller size for example
            return bip::managed_mapped_file(bip::open_or_create, "089f8a0f-956a-441d-9b9e-e0696c43185f", 10ul<<10);
        }
    }
    bip::managed_mapped_file _shm;
};

int main() {
    MyWorker instance;
}
