#include <stdio.h>
int main(void) {
    int c= 7;
    int x= 4;
    int* p= &x;
    int* q= &c;
    *p++;
    c= c+*p;
    printf("first=%d second= %d\n",*q,x);
}
