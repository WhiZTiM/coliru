#include <iostream>
#include <string>
#include <functional>

int max(int a, int b) {
    int isNegative = ((a-b) >> 31);
    return (isNegative & b) + ((~isNegative) & a);
}

int other(int a, int b)
{
    std::cout << ((a ^ 1) && (b ^ 1)) << std::endl;
    int isOne = ((a ^ 1) && (b ^ 1)) * 1;
    int isTwo = ((a ^ 2) && (b ^ 2)) * 2;
    int isThree = ((a ^ 3) && (b ^ 3)) * 3;
    return max(isOne, max(isTwo , isThree));
}

int main()
{
    std::cout<<"Other 2,3: " << other(2, 3) << std::endl; 
    std::cout<<"Other 1,2: " << other(1, 2) << std::endl; 
    std::cout<<"Other 1,3: " << other(1, 3) << std::endl; 
    std::cout<<"Other 1999,777: " << other(1999, 777) << std::endl; 
    std::cout<<"Other -3,-1000: " << other(-3, -1000) << std::endl; 
}
