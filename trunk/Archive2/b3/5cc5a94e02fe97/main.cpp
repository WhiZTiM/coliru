#include <stdio.h>
#include <float.h>

int main()
{
    int width = 1;
    bool equal = (width - FLT_EPSILON == width);
    printf(equal ? "equal" : "not qeual");

    return 0;
}