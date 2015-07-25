#include <iomanip>
#include <iostream>

int main() {
    double dollars = 29.50;
    
    std::cout.precision(2);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    
    std::cout << "$" << dollars << '\n';
    
    std::cout.imbue(std::locale("en_US.utf8"));
    std::cout << std::showbase << std::put_money(dollars*100);
}