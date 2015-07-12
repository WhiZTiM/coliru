#include <iostream>

std::string str;
#define pointTo(x,y) do{ str = #y; x=&y;   }while(0)

int main()
{
    
    int* x , hiThere ,helloWorld;
    pointTo(x,hiThere);
    std::cout<<str<<"\n";
    pointTo(x,helloWorld);
    std::cout<<str<<"\n";    
}