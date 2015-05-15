#include <iostream>
#include <string>
#include <vector>

#define x noreturn

[[x]] void fun(){}

int main()
{
    fun();
}
