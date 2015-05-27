#include <iostream>
#include <string.h>

int main() {
    std::cout << sizeof(__FILE__)-1 << " " << strlen(__FILE__);
}