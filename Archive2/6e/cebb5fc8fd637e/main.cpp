#include <memory>
#include <boost/shared_ptr.hpp>
#include <iostream>

int main() {
    boost::shared_ptr<int[]> ptr(new int[5]);
    int* deref = *ptr;
}