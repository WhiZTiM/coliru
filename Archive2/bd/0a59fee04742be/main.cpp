#include <iostream>
#include <string>
#include <vector>

int main() {
    int i = 1;
    // Почему это не работает ??/
    i += 1000;
    std::cout << "Значение i: " << i << std::endl;
}
