
#include <cstdint>
#include <cassert>
#include <cctype>
#include <string>

struct Char3Sequence { char data[3]; };

std::string toString(Char3Sequence seq)
{
    return std::string(seq.data, 3);
}

bool isAlpha(int ch) // cannot use std::isalpha(), because of locales
{
    return (ch >= 'A') && (ch <= 'Z');
}
    
uint16_t compress(const char* str) // \pre strlen(str) >= 3
{
    int ch0 = toupper(str[0]); assert(isAlpha(ch0));
    int ch1 = toupper(str[1]); assert(isAlpha(ch1));
    int ch2 = toupper(str[2]); assert(isAlpha(ch2));
    
    ch0 -= 'A';
    ch1 -= 'A';
    ch2 -= 'A';
        
    return (ch0 << 10) | (ch1 << 5) | ch2;
}
    
Char3Sequence decompress(uint16_t value)
{
    Char3Sequence seq;
    
    seq.data[0] = char(((value >> 10) & 0x1F) + 'A');
    seq.data[1] = char(((value >>  5) & 0x1F) + 'A');
    seq.data[2] = char(((value      ) & 0x1F) + 'A');
    
    return seq;
}

int main()
{
    auto compressed1 = compress("aaa");
    auto compressed2 = compress("AAA");
    
    assert( compressed1 == compressed2 );
    assert( toString(decompress(compressed1)) == "AAA" );
    
    auto compressed3 = compress("zzz");

    assert( compressed1 < compressed3 );
    assert( toString(decompress(compressed3)) == "ZZZ" );
    
}
