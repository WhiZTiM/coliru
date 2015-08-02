#include <iostream>
#include <locale>
int main()
{
    std::wstring str = L"Country: CANADÁ\nNumber: ";

    std::ios::sync_with_stdio(false);
    std::wcout.imbue({std::locale("en_US.utf8"), std::locale{}, std::locale::numeric});
    std::wcout << str << 3872 << '\n';
}