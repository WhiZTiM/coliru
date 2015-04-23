#include <iostream>
#include <string>

using namespace std;

int main()
{
    int *iptr = 0;
    char *cptr = 0;

    iptr++;
    cptr++;

    printf("%lx ? %lx\n", (size_t)iptr, (size_t)cptr);
    
    return 0;    
}