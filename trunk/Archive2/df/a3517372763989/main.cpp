#include <iostream>
#include <string>
#include <vector>

//Cycle detection algorithm, return period
template<class F,class T>
uint floyd(F f,T x0)
{
    T tortoise = f(x0), //f(x0) is the element/node next to x0.
      hare = f(f(x0));
    while(tortoise != hare)
    {
        tortoise = f(tortoise);
        hare = f(f(hare));
    }
    uint lam = 1;
    hare = f(tortoise);
    while(tortoise != hare)
    {
        hare = f(hare);
        lam += 1;
    }
    return lam;
}

int main()
{
    //LCG - parameters as used by gcc's rand()
    auto lcg = [](int x){ return ( (1103515245*x + 12345) % 2147483648 ); };
    unsigned int m = 10;
    auto lcgmod = [&](int x){ return lcg(x) % m; };
    std::vector<int> v = {1, 2, 3, 4, 1, 5, 6};

    int period_10 = floyd(lcgmod, 1);
    for(int i = 0, x = 1; i < 2*period_10; ++i)
    {
        std::cout << (x = lcgmod(x)) << ", ";
    }
    std::cout << std::endl;

    int c = 0;
    for(m = 2; m < 2000; ++m)
    {
        unsigned int p = floyd(lcgmod, 1);
        if(p != m)
            ++c;
        if(p == 0)
            std::cout << "Not recurring!" << std::endl;
    }
    std::cout << "Found " << c << " complete period series with seed as 1" << std::endl;
}