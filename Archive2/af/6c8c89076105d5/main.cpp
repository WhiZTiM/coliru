#include <ctime>
#include <iostream>
#include <locale>
 
int main()
{
    std::locale::global(std::locale("utf8"));
    std::time_t t = std::time(NULL);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t))) {
        std::cout << mbstr << '\n';
    }
}