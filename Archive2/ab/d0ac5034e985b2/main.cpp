#include <iostream>
void f(char *p[3])
{
    std::cout<<sizeof(p)<<'\n';
}

int main()
{
    char *p[3];
    std::cout<<sizeof(p)<<'\n';
    f(p);
}