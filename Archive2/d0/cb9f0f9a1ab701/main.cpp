
#include <iostream>

inline void cpy(char* p, const char* q)
{
 while (*p++ = *q++) ;
}


int main(int argc, char *argv[])
{
    const char* tocopy = "tocopy string";
    char cp[200];
    cpy(cp,tocopy);
    std::cerr << cp << std::endl;
}