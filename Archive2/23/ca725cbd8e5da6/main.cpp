#include <iostream>

template <typename T> void printtype(const T& value);

template <> void printtype<signed int>(const signed int& value) {
    std::cout << "signed value" << std::endl;
}

template <> void printtype<unsigned int>(const unsigned int& value) {
    std::cout << "unsigned value" << std::endl;
}

int main() 
{
    unsigned int ui = 10;
    signed int si = -15;
    
    printtype(ui);
    printtype(si);
    printtype(ui - si);
    printtype(si - ui);
}
