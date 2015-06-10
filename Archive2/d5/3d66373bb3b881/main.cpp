#include <iostream>

int addTwo(int n1, int n2)
{
    return n1 + n2;
}

int main()
{
    int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int starter = addTwo(numbers[0], numbers[1]);
    for (int i = 2; i < 10; ++i)
        starter = addTwo(starter, numbers[i]);
    std::cout << starter;
}