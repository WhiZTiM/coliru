#include <iostream>

void swopint(int& a, int& b)
{
    auto c = a;
    a = b;
    b = c;
}

int main()
{
    int n = 9;
    int m = 7;
    swopint(n,m);
    std::cout << "n = " << n << "\n";
    std::cout << "m = " << m << "\n";
}