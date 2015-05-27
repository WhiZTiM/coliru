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

struct Base {
    virtual int foo(const A&, int b) = 0;
    virtual ~Base() {}
};

struct B : Base {
    B() = default;
    B(const B&) = delete;
    B& operator=(const B&) = delete;

    int foo(const A&, int b) override {
        return -b;
    }
};

int main() {
    A a;
    std::shared_ptr<Base> b = std::make_shared<B>();
    std::vector<int> values{1, 2, 3, 2};
    
    using std::placeholders::_1;
    int min = *boost::min_element(values | boost::adaptors::transformed(
            std::bind(&Base::foo, b.get(), std::ref(a), _1)));
    
    std::cout << min << std::endl;
}

