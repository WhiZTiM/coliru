#include <string.h>
#include <stdio.h>

unsigned int decode(const char *obfuscator, const char *source, char *buffer, unsigned int size)
{
    unsigned short src = 0, obf = 0, dst = 0;
    unsigned int len = 0;
    const char *ptObf = obfuscator;

    while ((src = (unsigned short)*source++) != '\0' && len < size - 1)
    {
        obf = (unsigned short)*ptObf++;
        if (obf == '\0')
        {
            ptObf = obfuscator;
            obf = *ptObf++;
        }

        unsigned short hlp = src - 'A';

        src = *source++;
        if (src == '\0')
            break;

        hlp |= ((src - 'a') << 4);

        dst = (hlp ^ obf) - obf;
        buffer[len++] = dst;
    }

    buffer[len] = '\0';

    return len;
}

int main(int argc, char *argv[])
{
    char dbBuffer[1024];
    memset(&dbBuffer[0], 0, 1024);

    decode("OBFUSCATOR VALUE", "OBFUSCATED PASSWORD", dbBuffer, 1024);
    printf("Decoded: %s\n", &dbBuffer[0]);

    return 0;
}