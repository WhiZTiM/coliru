#include <stdio.h>
int main()
{
    int sum = 0;
    for (int i = 50; i < 251; ++i)
    {
        sum += i;
    }
    printf("%d\n", sum);
}