#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <openssl/sha.h>

// simple hex-print utility
void hex_print(const void *buf, size_t n)
{
    const unsigned char *beg = buf, *end = beg+n;
    while (beg != end)
        printf("%02x", *beg++);
    fputc('\n', stdout);
}


// iterate n-times
void hashcwe_n
(
    unsigned short n,   // iteration count
    void *src,          // source bytes
    size_t slen,        // souce length
    void *dst           // target buffer
)
{
    unsigned char md1[SHA_DIGEST_LENGTH];
    unsigned char md2[SHA_DIGEST_LENGTH];
    unsigned char *p1 = md1, *p2 = md2;
    unsigned short i;
    
    if (n == 0)
        return;
    
    // perform initial digest
    SHA1(src, slen, md1);
    
    // iterate the remainder of the loop
    for (i=0; i<(n-1); ++i)
    {
        unsigned char *tmp = p1;
        SHA1(p1, SHA_DIGEST_LENGTH, p2);
        p1 = p2;
        p2 = tmp;
    }
    memcpy(dst, p1, SHA_DIGEST_LENGTH);
}

// main entry point
int main()
{
    unsigned char data[] = {0x61,0x62,0x63}; // "abc"
    unsigned char md[SHA_DIGEST_LENGTH] = {0};
    
    hashcwe_n(USHRT_MAX, data, sizeof(data), md);
    hex_print(md, SHA_DIGEST_LENGTH);
    
    return 0;
}
