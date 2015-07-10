#include <iostream>
#include <string>
#include <vector>

void fun(int a[]){
    std::cout <<sizeof(a);
}

int main()
{
    int a[5]{};
    fun(a);
}
