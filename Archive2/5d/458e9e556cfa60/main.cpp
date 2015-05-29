#include <iostream>
#include <string>
#include <ctime>

int main()
{
    time_t a;
    struct tm *timeInfo;
    time(&a);
    timeInfo = localtime(&a);
    std::cout << sizeof(time_t)  << std::endl;
}
