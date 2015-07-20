#include <iostream>
#include <typeinfo>

float func() {return 1;}

int main() {
    auto exit = (int (*)()) &func;
    
    std::cout << exit() << std::endl;
}