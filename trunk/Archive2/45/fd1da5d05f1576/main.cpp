#include <iostream>

int main()
{

    const int size = 10;
    int a[size] = { 19, 6, 32, 17, 5, 44, 42, 93, 1, 8 };
    int result = a[0];
    for(int* p = a; p < a + size; ++p) {
        if(*p > result)
        {
            result = *p;
        }
        //std::cout << *p << '\n';
    }
    std::cout << result;
}