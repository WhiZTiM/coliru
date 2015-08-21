#include <iostream>
#include <cstdlib>
#include <cstring>

int main()
{
    char buf[18];
    char buf2[18];
    int newlength = 16;
    memset(buf, '0', 16);
    for (int i = newlength; i < 18; i++)
        buf[i] = 0x00;

    memcpy(buf2, buf, 18);

    return 0;
}
