#include <iostream>   
#include <cstdlib> 
 
int main() 
{
    int* p1 = (int*)std::malloc(4*sizeof(int));  // allocates enough for an array of 4 int
    int* p2 = (int*)std::malloc(sizeof(int[4])); // same, naming the type directly
    int* p3 = (int*)std::malloc(4*sizeof *p3);   // same, without repeating the type name
 
    if(p1) {
        for(int n=0; n<4; ++n) // populate the array
            p1[n] = n*n;
        for(int n=0; n<4; ++n) // print it back out
            std::cout << "p1[" << n << "] == " << p1[n] << '\n';
    }
 
    std::free(p1);
    std::free(p2);
    std::free(p3);
}