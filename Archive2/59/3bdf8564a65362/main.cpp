#include <iostream>
#include <string>
#include <vector>

struct foo
{
    int a;
    int b;
};

int main()
{
   struct foo bar = { .a = 1, .b = 2 };
   (void)bar;
   return 0;
}
