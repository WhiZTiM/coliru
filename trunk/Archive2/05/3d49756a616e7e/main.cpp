#include <cassert>

int main()
{
    static_assert(0 == '\0', "wat");
    char a = 0;
    char b = '\0';
    assert(a == b);
}
