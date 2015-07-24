#include <iostream>

template<typename ...Args>

void printer(Args... args) {
    (std::cout << ... << args) << '\n';
}
int main()
{
    printer("HOLY SHIT IS IT REAL IS IT REAL");
}