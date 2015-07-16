#include <unistd.h>
#include <stdio.h>


int main()
{
    printf("%d\n", sysconf(_SC_OPEN_MAX));

    return 0;
}
