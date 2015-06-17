#include <iostream>
struct monitor {
    virtual int price() const = 0; // virtual, meaning ignore and go straight to other subclasses,
};

struct nineteenInchMonitor : monitor {
    int price() const { return 99; }
};
struct twentyInchMonitor : monitor {
    int price() const { return 129; }
};

int sell(monitor const &mon) {
    return mon.price(); // get price() of smallMonitor, type nineteenInchMonitor
}

int main() {
    nineteenInchMonitor smallMonitor;
    twentyInchMonitor bigMonitor;               // makes nineteenInchMonitor, type smallMonitor
    std::cout << sell(bigMonitor) << std::endl; // pass reference on to sell
}
