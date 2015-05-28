#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm.hpp>

#include <iostream>
#include <functional>
#include <memory>

struct A {
    A() = default;
    A(const A&) = delete;
    A& operator=(const A&) = delete;
};

struct B {
    B() = default;
    B(const B&) = delete;
    B& operator=(const B&) = delete;

    int foo(const A&, int b)  {
        return -b;
    }
};

int main() {
    A a;
    auto b = std::make_shared<B>();
    std::vector<int> values{1, 2, 3, 2};
    
    using std::placeholders::_1;
    auto fun = std::bind(&B::foo, b.get(), std::ref(a), _1);
    int min = *boost::min_element(values | boost::adaptors::transformed(fun));
    std::cout << min << std::endl;
}

