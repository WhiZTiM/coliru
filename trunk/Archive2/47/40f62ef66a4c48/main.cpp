#include <map>
#include <iostream>

struct HelloSean {
    int stuff;
    double goop;
    HelloSean() {
    }
    HelloSean(int a) {
        stuff = a;
        goop = a / 2.0;
    }
};

int main()
{
    std::map<int, HelloSean> seans;
    seans[10] = HelloSean(7);
    std::cout << seans[10].goop;
    return 0;
}
