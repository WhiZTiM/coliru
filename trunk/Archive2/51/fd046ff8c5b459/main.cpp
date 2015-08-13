#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdio.h>
 
int main(void)
{
    char *src = "Take the test.";
//  src[0] = 'M' ; // this would be undefined behavior
    char dst[strlen(src) + 1]; // +1 to accomodate for the null terminator
    strcpy(dst, src);
    dst[0] = 'M'; // OK
    printf("src = %s\ndst = %s\n", src, dst);
 
#ifdef __STDC_LIB_EXT1__
    int r = strcpy_s(dst, sizeof dst, src);
    printf("dst = \"%s\", r = %d\n", dst, r);
#endif
}