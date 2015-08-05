#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

int main()
{   
    int *ptr(0);
    ptr = new int();
    
    delete ptr;
    
    if(ptr)
        printf("ye");
}
