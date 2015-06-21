#include <stdio.h>

int main(void)
{
    const int a=5;
	static int b=a;
	printf("%d",b);
}