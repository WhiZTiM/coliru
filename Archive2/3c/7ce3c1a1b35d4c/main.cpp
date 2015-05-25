#include <iostream>
struct thing {
    thing() {
        std::cout << this << "\n";
        const_cast<thing*>(this)++;
        std::cout << this << "\n";
    }
};

int main() {
    thing t;
}