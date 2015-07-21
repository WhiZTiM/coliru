#include <iostream>

#include <boost/format.hpp>
#include <boost/phoenix.hpp>
#include <boost/phoenix/bind/bind_function.hpp>

#include <boost/function.hpp>
using namespace boost::phoenix::placeholders;
using namespace boost::phoenix;

int f2(int a, int b) {
    std::cout << boost::format("Called f2(%1%, %2%)") % a % b << std::endl;
    return 0;
}

int f3(int a, int b, int c) { 
    std::cout << boost::format("Called f3(%1%, %2%, %3%)") % a % b % c << std::endl;
    return 0;
}

void do2(boost::function<int (int, int)> const &cb2) {
    std::cout << boost::format("Calling cb2(%1%, %2%)") % 5 % 9 << std::endl;
    cb2(5, 9);
}

void do3(boost::function<int (int, int, int)> const &cb3) {
    std::cout << boost::format("Calling cb2(%1%, %2%, %3%)") % 6 % 8 % 3 << std::endl;
    cb3(6, 8, 3);
}


int main() {
    do2(bind(f3, _1, _2, 10));
    do3(bind(f2, _1, _2));
};

