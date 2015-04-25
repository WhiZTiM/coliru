#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/optional.hpp>
#include <iostream>

namespace bip = boost::interprocess;

struct MyWorker {

    int foo() {
        return ++*(shm().find_or_construct<int>("the_int")(42));
    }

  private:
    bip::managed_mapped_file& shm() {
        if (!_shm)
            _shm = bip::managed_mapped_file(bip::open_or_create, "shared", 10ul<<10);
        return *_shm;
    }
    boost::optional<bip::managed_mapped_file> _shm;
};

int main() {
    MyWorker instance;
    std::cout << instance.foo();
}
