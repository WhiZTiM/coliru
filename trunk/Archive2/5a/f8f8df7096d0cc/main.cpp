#include <stdlib.h>
#include <stdio.h>


int main () {
    int* k = malloc(sizeof(int[5]));
    k += 50000;
    k -= 49999;
    
    char* kc = (char*)k;
    kc += 3;
    *kc = '5';
    
    *(unsigned int*)k = 5;
    
    *(float*)k = 4;
    
    unsigned char t = *(unsigned char*)k;
}
