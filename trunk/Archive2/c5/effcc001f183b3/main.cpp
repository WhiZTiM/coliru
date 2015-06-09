#include <stdio.h>
#include <string.h>
 
int main(void)
{
    const char* lines[] = {
        "abc=1",
        "abc =2",
        "abc= 3",
        "abc=\t 4",
        "abc\t=\t5",
    };
 
    for( size_t i=0; i<sizeof(lines)/sizeof(lines[0]); i++ ) {
        int n = 0;
        int rc = sscanf(lines[i], "abc=%d", &n);
        
        printf("%ld. '%s' -> rc=%d, n=%d\n", i, lines[i], rc, n);
    }
    
    return 0;
}