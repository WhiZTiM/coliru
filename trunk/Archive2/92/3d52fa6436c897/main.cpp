#include <stdio.h>
typedef int foo;

int main()
{
    printf ("%zu\n", sizeof (foo)); /* #1 */

    char foo;
    printf ("%zu\n", sizeof foo); /* #2 */

    return 0;
}