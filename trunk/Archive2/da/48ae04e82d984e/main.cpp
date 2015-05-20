#include <iostream>
#include <string>
#include <vector>

int fun () {return 5;}

using foo = fun;

int main()
{
   return foo();
}
