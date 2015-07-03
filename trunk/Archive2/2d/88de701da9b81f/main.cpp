#include <iostream>
#include <locale>
#include <clocale>
#include <algorithm>
#include <codecvt>

// test if every character in a UTF-8 string is a letter
bool letters(std::string str)
{
    // this part of C++11 didn't come to gcc until version 5.0
    // (Microsoft and Clang had it in 2010 though)
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wstr = conv.from_bytes(str.data());
    return std::all_of(wstr.begin(), wstr.end(),
             [](wchar_t c){return std::isalpha(c, std::locale("en_US.utf8"));});
}

int main()
{
    // either this:
//    std::setlocale(LC_ALL, "en_US.utf8");
    // or this:
    std::ios::sync_with_stdio(false);

    std::cout.imbue(std::locale("en_US.utf8"));
    std::cout << "letters(" << "è" << ") returns "
              << std::boolalpha << letters("è") << '\n';
}