#include <iostream>
#include <string>
#include <vector>

int main() {
    int c = 1337;
    
    (c += 1) -= 1;

    std::cout << c << std::endl;
}
