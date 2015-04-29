#include <iostream>

int main()
{
    char* mx = "whatis" ;
    
    for (int i  = 0; i<7; i++) {
       std::cout<<"\n"<<mx[i];
    }
    printf("%lu",sizeof(mx));
    
    for (int i  = 0; i<6; i++) {
        std::cout<<"\n"<<mx[i];
    }
    printf("%lu",sizeof(mx));

}
