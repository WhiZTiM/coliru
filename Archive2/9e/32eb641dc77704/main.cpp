#include <iostream>
#include <string>
#include <unistd.h>

int main()
{
    char* c= "abc";
    void* p= &c;
    printf("%s %s", *(char**) p, *(char*) p);
                  
}
