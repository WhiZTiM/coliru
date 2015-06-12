#include <stdio.h>

int main()
{ 
    char *multiple = "0.20,0.37,0.75,0.56";
    char one[4];
    char two[4];
    char three[4];
    char four[4];

    sscanf(multiple, "%[^','] %[^','] %[^','],%[^',']", one, two, three, four);
    printf("one %s, two %s, three %s, four %s\n", one, two, three, four);

    return 0;
}