#include <iostream>
#include <string>
#include <vector>

int fun () {return 5;}

auto foo = fun;

int main()
{
   return foo();
}
