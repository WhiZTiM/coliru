#include <vector>

struct A {
    char a[3];
    using iter = decltype(std::begin(a));
};

int main()
{
    A::iter i;
    
}
