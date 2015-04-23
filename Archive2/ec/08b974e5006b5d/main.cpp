#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<int[]> p(new int[3] { 1,2,3 });

    std::cout << "Before: " << p[0] << ", " << p[1] << ", " << p[2] << ";\n";
    p[1] = 42;
    std::cout << "After:  " << p[0] << ", " << p[1] << ", " << p[2] << ";\n";
}
