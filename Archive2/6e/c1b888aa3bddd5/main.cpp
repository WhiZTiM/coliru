#include <iostream>


int main(int argc, char** argv) {
    int a[] = {1, 2, 2};
    std::cout << sizeof(a) / sizeof(a[0]) << "\n";
    return 0;
}