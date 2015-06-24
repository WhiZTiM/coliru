#include <stdio.h>

void g(int n) {
    printf("g(%d)\n", n);
}

int main() {
    int i = 12;
    
    char arr[i]; // VLA
    
    (void)sizeof *(g(1), &arr); // Prints "g(1)"
    (void)sizeof (g(2), arr);   // Prints nothing
    
    return 0;
}