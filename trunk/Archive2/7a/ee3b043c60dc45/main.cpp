#include <iostream>
#include <string>
#include <vector>

struct example {
    ~example() {
        std::cout << "rip" << std::endl;
    }
};

void test() {
    static example x;
}

int main() {
    test();
    std::cout << "stuff" << std::endl;
}
