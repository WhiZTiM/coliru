#include <stdio.h>

#define concat(a,b) a##b
#define funcgen(name) concat(func_, name)

#define mod d
void funcgen(mod)(void)
{ puts("Hi"); }
#undef mod
 
int main()
{
    func_d();
}