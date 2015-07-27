#include <cassert>
struct S {
    char c;  // 1 byte value
             // 3 bytes padding
    float f; // 4 bytes value
    bool operator==(const S& arg) const { // value-based equality
        return c == arg.c && f == arg.f;
    }
};


S s1 = {'a', 3.14};
S s2 = s1;
int main()
{
    assert(sizeof(S) == 8);
    reinterpret_cast<char*>(&s1)[2] = 'b'; // change 2nd byte
    assert(s1 == s2); // value did not change
}

