#include <iostream>
#include <locale>
#include <clocale>

bool letter(wchar_t a)
{
    return std::isalpha(a, std::locale("en_US.utf8"));
}

int main()
{
    // either this:
//    std::setlocale(LC_ALL, "en_US.utf8");
    // or this:
    std::ios::sync_with_stdio(false);

    std::wcout.imbue(std::locale("en_US.utf8"));
    std::wcout << "letter(" << L'è' << ") returns "
              << std::boolalpha << letter(L'è') << '\n';
}