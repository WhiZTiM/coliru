#include <stdio.h>
#include <stdlib.h>
#define NO_OF_CHARS 256

char* removedup(char* str)
{
    int binhash[NO_OF_CHARS]={0};
    int ip_index=0,res_index=0;
    char temp;

    while(*(str+ip_index))
    {
        temp = *(str+ip_index);
        if(binhash[temp] == 0)
        {
            binhash[temp] = 1;
            *(str+res_index) = *(str+ip_index);
            res_index++;
        }
        ip_index++;
    }
    *(str+res_index) = '\0';
    return str;
}


int main()
{
    char str[]="geeksforgeeks";
    printf("%s",removedup(str));
    return 0;
}
