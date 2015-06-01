#include <ctime>
#include <iostream>
#include <locale>
 
int main()
{
    std::locale::global(std::locale("en_GB.utf8"));
    std::time_t t = std::time(NULL);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "PPD-HS_%F_%T_%Z", std::localtime(&t))) {
        std::cout << mbstr << '\n';
    }
}