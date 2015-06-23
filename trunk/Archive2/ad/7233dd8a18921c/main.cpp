#include <stdio.h>

int cutoff(int n){
    int sum, count, nextOdd;
    for (sum=0, count=1, nextOdd = 0; nextOdd <=n; nextOdd = 1 + 2*(count++ - 1)){
        sum +=nextOdd;
    }
    return sum;
}

int main()
{
// printf("Enter a positive odd integer: \n");
 int c = 6;
// scanf("%d",&c);
 printf("The sum of odd numbers from 1 to %d is %d.\n", c, cutoff(c));
}