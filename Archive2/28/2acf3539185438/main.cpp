#include <cstdio>
#include <clocale>
#include <ctime>
#include <cwchar>
 
int main()
{
    std::setlocale(LC_ALL, "en_US.UTF-8"); // the C locale will be the UTF-8 enabled English
    std::setlocale(LC_NUMERIC, "de_DE");   // decimal dot will be German
    std::setlocale(LC_TIME, "ja_JP");      // date/time formatting will be Japanese
    wchar_t str[100];
    std::time_t t = std::time(nullptr);
    std::wcsftime(str, 100, L"%A %c", std::localtime(&t));
    std::wprintf(L"Number: %.2f\nDate: %Ls\n", 3.14, str);
}