#include <stdio.h>
#include <ctype.h>

#define mprint(str, e) (printf("%s = ", str), _Generic((e), \
    int: printf("%d", (e)),    \
    char: printf("%c", (e)),   \
    float: printf("%f", (e)),  \
    long: printf("%ld", (e)),  \
    char *: printf("%s", (e))))

#define print(...) mprint(#__VA_ARGS__, (__VA_ARGS__))

int main(void)
{
    print(int a = isalnum('a'));
    return 0;   
}