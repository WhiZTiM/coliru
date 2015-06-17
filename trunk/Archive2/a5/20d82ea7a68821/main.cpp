#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j;
    int my_array[10][10];

    //Fill the array
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            my_array[i][j] = 10*i + j;
        }
    }
    
    //Print out the array
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", my_array[i][j]);
        }
        printf("\n");
    }
    
    
    return 0;
}