#include <iostream>

int & dangling()
{
    int i = 5;
    return i;
}

int main()
{
}
