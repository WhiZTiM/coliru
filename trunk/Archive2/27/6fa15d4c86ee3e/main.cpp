#include <cassert>
#include <type_traits>

int main()
{
    static_assert(0 == '\0', "wat");
    static_assert(std::is_same<decltype(0),decltype('\0')>::value, "0 is not the same type as '\\0'");
    char a = 0;
    char b = '\0';
    static_assert(std::is_same<decltype(a),decltype(0)>::value, "0 changed types going into a");
    static_assert(std::is_same<decltype(b),decltype('\0')>::value, "'\\0' changed types going into b");
    assert(a == b);
}