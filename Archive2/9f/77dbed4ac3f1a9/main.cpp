#include <cassert>
#include <cstdlib>

namespace
{
    
char a[100];
char b[10];

void
f(char x[100])
{
    static_cast< void >(x);
}

void
g(char (& y)[100])
{
    static_cast< void >(y);
}

}

int main() 
{
    f(a);
    f(b);
    g(a);
    g(b);
    return EXIT_SUCCESS;
}

