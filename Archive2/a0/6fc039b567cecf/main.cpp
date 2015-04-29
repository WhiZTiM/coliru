#include <iostream>
#include <array>

int main()
{
    char* mx = "whatis" ;
    
    for (int i  = 0; i<7; i++) {
        printf("\n%c",mx[i]);
    }
    printf("%lu",sizeof(mx));
    
    for (int i  = 0; i<6; i++) {
        printf("\n%c",mx[i]);
    }
    printf("%lu",sizeof(mx));

}
