#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main ( int argc, char** argv )
{
    int nombreMystere = 0;
    const int MAX = 20, MIN = 1;
     
    srand(time(NULL));
    nombreMystere = (rand() % (MAX - MIN + 1)) + MIN;
 
 
    printf("%d est le nombreMystere\n");
 
return 0;
}