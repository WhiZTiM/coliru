#include <cstdint>
#include <cstdio>
#include <cassert>

int main()
{
    char * cstring = new char[1];
    cstring[0] = 0;
    assert(cstring == "");
}
