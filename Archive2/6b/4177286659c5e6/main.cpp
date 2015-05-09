#include <stdio.h>
#include <string.h>

int my_atoi( const char * str )
{
    int val = 0;
    while( *str ) {
        val = val*10 + (*str++ - '0');
    }
    return val;
}

int my_strlen(const char *str){
    
    int length = 0;
    while(str[length]!='\0')
    {
        length++;
    }
    return length;
}

/*
void customSort(int values[], char words[][])
{
     int i, j, index;
     char[] wordIndex;
     
     for (i = 1; i < sizeof(values); ++i)
     {
          index = values[i];
          wordIndex = words[i];
          
          for (j = i; j > 0 && values[j-1] > index; j--)
               values[j] = values[j-1];
               words[j] = words[j-1];

          values[j] = index;
          words[j] = wordIndex;
     }
}
*/

char * SumCharsAndDigits(const char* str){
    
    const char *numbers = "1234567890", *lower = "abcdefghijklmnopqrstuvwxyz", *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static char result;
    int total = 0;
    char *mystring = (char*)str;
    char *c = mystring;
    while (*c)
    {
        if (strchr(numbers, *c))
        {
           total += my_atoi(c);
        }
        else if (strchr(lower, *c))
        {
           total += (my_atoi(c)-48);
        }
        else if (strchr(upper, *c))
        {
           total += (my_atoi(c)-16);
        }
        c++;
    }
    
    result = char(total);
    return &result;
} 

void PrintWordsSorted(const char* str){
    
    char * pch;
    pch = strtok ((char *) str," ");
    while (pch != NULL)
    {
        char *p = SumCharsAndDigits(pch);
        printf ("%s, %d\n",pch,*p);
        pch = strtok (NULL, " ");
    }
}
 
int main()
{
    char str1[] = "ab1!";
    char *p = SumCharsAndDigits(str1);
    printf("%d\n\n", *p);
    
    char str2[] = "mon code n'est pas cool !";
    PrintWordsSorted(str2);
    return 0;
}