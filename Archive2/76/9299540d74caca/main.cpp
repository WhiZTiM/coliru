#include <iostream>
#include <string>
#include <vector>

int * i;

void f(const int & x){
i = &x;
* i = 16;}

int main()
{
    int outside = 2;
    std::cout << outside << std::endl;
    f(outside);
    std::cout << outside << std::endl;
    std::cout << *i;
    
   
}
