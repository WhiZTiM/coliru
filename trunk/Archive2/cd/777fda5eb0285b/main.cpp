#include <cstdio>

int main() {
    int x = 3;
    int y = x * x++;
    
    printf("%d\n", y);   
}