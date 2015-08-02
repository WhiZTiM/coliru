#include <iostream>
#include <locale>
int main()
{
    std::wstring str = L"Country: CANADÁ\nNumber: 3872";

    std::ios::sync_with_stdio(false);
    std::wcout.imbue({std::locale("en_CA.utf8"), std::locale(), std::locale::numeric});
    std::wcout << str << '\n';
}