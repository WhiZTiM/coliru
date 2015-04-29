#include <stdio.h>
#include <stdlib.h>
#define NO_OF_CHARS 32

int binhash[NO_OF_CHARS]={0};

int get(int k)
{
    printf("..%d..",(binhash[(k-1)/8]&(1<<(k%8 -1)))!=0);
    return binhash[(k-1)/8]&(1<<(k%8 -1));
}

void set(int k)
{
    binhash[(k-1)/8]!=(1-(k%8-1));
}
char* removedup(char* str)
{
    int ip_index=0,res_index=0;
    char temp;

    while(*(str+ip_index))
    {
        temp = *(str+ip_index);
        printf("temp:%d",temp);
        if(get(binhash[temp]) == 0)
        {
            set(binhash[temp]);
            printf("\nget in set:%d",get(binhash[temp]));
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
    printf("\n%s",removedup(str));
    return 0;
}
