#include <iostream>
#include <string>

struct symname{ const char* DP; };

struct symname getSymName[4];

void init_allArrays(){
        getSymName[0].DP = "name0";
        getSymName[1].DP = "name1"; 
        getSymName[2].DP = "name2"; 
        getSymName[3].DP = "name3"; 
}


int main()
{
    std::cout << "test!" << std::endl;

}