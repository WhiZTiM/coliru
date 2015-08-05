#include <iostream>

class adder {
public:
    adder(int x) : x(x) { }

    int operator()(int y) const {
        return x + y;
    }

private:
    int x;
};

int main() {
    adder add5(5);
    std::cout << add5(2) << '\n';
    return 0;
}