#include <stddef.h>

void fun(int x[static 10])
{
}

int main(void)
{
    fun(NULL); // error
    
    int x[5]; // too short
    fun(x); // error
}