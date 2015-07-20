#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
using namespace std;


int main()
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    const char val[] = "+3°C";
    wstring text = converter.from_bytes(val);

    return 0;
}