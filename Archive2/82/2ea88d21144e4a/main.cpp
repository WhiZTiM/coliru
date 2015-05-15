#include <memory>
#include <boost/shared_ptr.hpp>
#include <iostream>

int main() {
    boost::shared_ptr<int[5]> ptr(new int[5]);
    int[5] deref = *ptr;
}