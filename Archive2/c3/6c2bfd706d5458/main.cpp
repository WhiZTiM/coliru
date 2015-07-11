#include <iostream>
#include <string>
#include <vector>


template<class T>
class TD;

int main()
{
    int x = 10;
    auto&& arg = &x;
    TD<decltype(arg)> td1;
}
