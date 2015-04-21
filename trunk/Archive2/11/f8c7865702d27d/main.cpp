#include <iostream>

struct T {
    static const size_t value = 10;
};

// const size_t T::value;

int main()
{
    int testArray[T::value] = { -1 };
    std::cout << &T::value << ", " << testArray[0];
    return 0;
}
