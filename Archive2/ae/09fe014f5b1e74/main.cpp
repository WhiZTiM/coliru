#include <iostream>
#include <string>
#include <vector>

int * i;

void f(int& x){
i = &x;
x = 16;}

int main()
{
    int outside = 2;
    std::cout << outside << std::endl;
    f(outside);
    std::cout << outside << std::endl;
    std::cout << *i;
    
   
}
