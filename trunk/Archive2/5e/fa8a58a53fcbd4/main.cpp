#include <stdio.h>


int main()
{
    int a[] = { 1, 2, 3 }; // a is an array. it's not a pointer.
    int *p = a; // p is a pointer. it's not an array.
    printf("%zu %zu\n", sizeof a, sizeof p);
}
