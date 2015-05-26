#include <stdio.h>

template <int n>
struct factorial {
    enum { value = n * factorial<~-n>::value };
};
 
template <>
struct factorial<0> {
	enum { value = 1 };
};

int main()
{
    printf("5! = %d\n", factorial<5>::value);
    return 0;
}
