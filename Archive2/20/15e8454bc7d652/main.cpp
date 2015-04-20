constexpr unsigned int f_orig(unsigned n, unsigned p)
{
    return (n*2-1)%p;
}

constexpr unsigned int f_Columbo(unsigned n, unsigned p) 
{
    return ((n % p)*2 - 1) % p;
}

#include <iostream>

int main() {
    int n = 5;
    int p = 5;
    std::cout << "f_orig("<<n<<", "<<p<<") == "<<f_orig(n, p)<<"\n";
    std::cout << "f_Columbo("<<n<<", "<<p<<") == "<<f_Columbo(n, p)<<"\n";
}