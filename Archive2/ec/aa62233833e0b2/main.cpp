#include<stdio.h>
int main(){
    int i = 1;
    printf("%d %d %d\n", i++, i++, i);
    printf("%d %d %d %d\n", i++, i++, i++, i);
    printf("%d %d %d %d %d\n", i++, i++, i++, i++, i);
    printf("%d %d %d %d %d %d\n", i++, i++, i++, i++, i++, i);
    printf("%d %d %d %d %d %d %d\n", i++, i++, i++, i++, i++, i++, i);
    return 0;
}