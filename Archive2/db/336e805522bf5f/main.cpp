#include <stdio.h>
#include <stdlib.h>
#define NO_OF_CHARS 32

int binhash[NO_OF_CHARS]={0};

//Get particualr bit of a byte
int get(int k)
{
    return binhash[(k-1)/8]&(1<<(k%8 -1));
}
// set particular bit of a byte
void set(int k)
{
    binhash[(k-1)/8]|=(1<<(k%8-1));
}
char* removedup(char* str)
{
    int ip_index=0,res_index=0;
    char temp;

    while(*(str+ip_index))
    {
        temp = *(str+ip_index);
        //check weather that particulat bit is set or not
        if(get(temp) == 0)
        {
            // set particular bit
            set(temp);
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
    printf("\n%s\n",removedup(str));
    return 0;
}
