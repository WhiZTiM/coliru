#include <iostream>


int main()
{
   int *a = new int;
    *a = 10;
    int *b;
    b = a;
    
    std::cout << *b;
   
    return 0;  
}
