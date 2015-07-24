#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <string>


int main()
{
    char s[] = "01234567";
    strncpy(s, "AA", 2);
    printf("%s", s);

    return 0;
}