#include <cassert>
#include <cstdlib>

namespace
{
    
char a[100];
char b[10];
char * c = nullptr;

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
    f(c);
    g(a);
    //g(b); // no matching function for call to 'g'
    //g(c); // no matching funciton for call to 'g'
    return EXIT_SUCCESS;
}

