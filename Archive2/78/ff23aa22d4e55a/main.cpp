#include <utility>
#include <stddef.h>

template <typename CharType, size_t Size>
class StringT {};

template <size_t N>
void GetProperty(StringT<char, N>& val)
{
}

void GetProperty(bool val) {}

void GetProperty(int val) {}

int main()
{
    StringT<char, 512> str1;
    GetProperty(str1);
    
    StringT<char, 1024> str2;
    GetProperty(str2);
}
