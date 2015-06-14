#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

int k, seed, mines, row, column, boom;
int board[9][10];
printf("Please enter your seed: ");
scanf("%d", &seed); getchar();
srand(seed);
for(k = 1; k <= mines; k++) {
    row = rand() % 8;                 //error:called object type int is not a function or function pointer
    column = rand() % 8;              //error:called object type int is not a function or function pointer
    //if(board[row][column] == 0) {
      //  board[row][column] = boom;

    //}
}
}