#include<stdio.h>

void charcount(char* str)
{
    int counter=1;
    while(*(str))
    {
        if(*str == *(str+1))
            counter++;
        else
        {
            printf("%c%d",*(str),counter);
            counter=1;
        }
        str++;
    }
}


int main()
{
    char str[]="aaabbbccc";
    charcount(str);
}
