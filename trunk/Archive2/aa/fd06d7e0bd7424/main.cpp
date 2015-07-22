#include <inttypes.h>
#include <stdio.h>

#define S_(x) #x
#define S(x) S_(x)

int main()
{
    printf("%s\n", S(PRId64));
}
