#include <iostream>
#include <string>
#include <vector>

int main() {
    int c = 1337;

    // c++;             // fine
    // c--;             // fine
    // c++--;           // ERR
    // (c++)--;         // ERR
    // (int) (c++)--;   // ERR
    // ((int) (c++))--; // ERR

    // c += 1;          // fine
    // c -= 1;          // fine
    (c += 1) -= 1;      // lol

    std::cout << c << std::endl;
}
