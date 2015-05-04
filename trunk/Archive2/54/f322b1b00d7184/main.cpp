#include <stdio.h>

template <typename T, typename U> constexpr int DoTest()
{
    return sizeof(T) + sizeof(U);
}

template <typename T, typename U> struct Dummy
{
	enum { Result = DoTest<T, U>() };
};

int main(int, char**)
{
    printf("value: %d\n", Dummy<int, char>::Result);
	return 0;
}

