#include <iostream>
#include <string>
#include <vector>
#include <array>

class foo
{
public:  
    foo(): boo() {}
    foo(const foo &fromParams): boo(fromParams.boo)
    {}
char boo[64];
    
};

int main()
{
  
   
}
