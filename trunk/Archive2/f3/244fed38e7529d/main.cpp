#include <functional>
#include <iostream>

// std::function-returning-int param in ctor with default value
// This works fine

class PrInc; // "print and increment"

using Worker = std::function<int(int)>;

int foo(int i) {
    std::cout << i << std::endl;
    return i+1;
}

class PrInc {
  public:
    PrInc(int i, Worker fn = foo) : i_(i), fn_(fn) {}
    int operator()() { return fn_(i_); }
  private:
    int i_;
    Worker fn_;
};

// std::function-returning-PrInc2 param in ctor with default value
// This fails, at least on g++ 4.8.2 --std=c++11

class PrInc2;

using Factory = std::function<PrInc2(int)>;
// Use function ptrs (instead of std::function<>s) and it works fine
//typedef PrInc2 (*Factory)(int);

PrInc2 bar(int);

class PrInc2 {
  public:
    PrInc2(int i, Factory fn = Factory(bar)) : i_(i), fn_(fn) {}
    PrInc2 operator()() { return fn_(i_); }
  private:
    int i_;
    Factory fn_;
};

PrInc2 bar(int i) {
    std::cout << i << std::endl;
    return PrInc2(i+1);
    // error: could not convert 'bar' from 'PrInc2 (*)(int) to 'Factory {aka std::function<PrInc2(int)>'
}

int main() {
    auto p1 = PrInc {1};
    auto p2 = PrInc{p1()};
    p2();

    auto p3 = PrInc2 {1};
    // error: could not convert 'bar' from 'PrInc2 (*)(int) to 'Factory {aka std::function<PrInc2(int)>'
    auto p4 = p3();
    p4();

    return 0;
}