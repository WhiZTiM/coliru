#include <iostream>

int main()
{
    std::cout << [](int day, int month, int year) { return (497 * (year - 1) / 400 + (int[]){ 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 }[month - 1] + day + (int)(year % 4 == 0 && month > 2 && (year % 100 != 0 || year % 400 == 0))) % 7; }(4, 8, 2015);

    return 0;
}