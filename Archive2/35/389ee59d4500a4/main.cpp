#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main () {
    int A[2] = { 1, 2 };
    int a = A[1];
    int b = *(int*)((char*)A + sizeof(int));
    assert(a == b);
}
