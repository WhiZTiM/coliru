#include <stdio.h>
typedef int foo;

int main(int argc, char *argv[])
{
    printf ("%u\n", sizeof foo); /* #1 */

    char foo;
    printf ("%u\n", sizeof foo); /* #2 */

    return 0;
}