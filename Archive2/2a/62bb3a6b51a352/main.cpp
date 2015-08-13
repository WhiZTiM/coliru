#include <string.h>
#include <stdio.h>

void reverse(char *str)   
{    
    size_t a = 0;
    size_t b = strlen(str) - 1;

    while(a < b)
    {
        // Swap str[a] and str[b]
        char t = str[a];
        str[a] = str[b];
        str[b] = t;

        ++a;
        --b;
    }
}

int main(void) {
    char str[] = "Hello, World !";
    reverse(str);
    puts(str);
}
