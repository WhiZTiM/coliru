#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <string>


int main()
{
    int a = -1;
    unsigned int b = (unsigned char(a) & 0xff);

    printf("%u", b);

    return 0;
}