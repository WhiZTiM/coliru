#include <iostream> 
 
#define X Hello
#define Y world 
 
#define C X
#define D Y

#define M C
#define N D
 
#define _CONCAT(A, B) #A #B 
#define CONCAT(A, B) _CONCAT(A, B) 
 
int main() { 
    std::cout << CONCAT(M, N) << std::endl; 
    return 0; 
} 