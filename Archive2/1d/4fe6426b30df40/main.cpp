#include<stdio.h>  

int main() {
    //clrscr();
    int line, i;

    char (*string)[100];
    printf("How many line?\n");
    scanf("%d",&line);
    getchar();

    for(i=0;i<line;i++) {
        gets(string[i]);
    }

    printf("You entered:\n");
    for(i=0;i<line;i++) {
        puts(string[i]);
    }

    return 0;
}