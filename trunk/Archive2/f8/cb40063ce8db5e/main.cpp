#include <string.h>
#include <stdio.h>

int main(void) {
    char* A    = "TEST";
    char  B[4] = "TEST";
    printf("strcmp(A, B) = %d", strcmp(A, B));
}
