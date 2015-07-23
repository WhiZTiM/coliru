#include <iostream>
#include <codecvt>
int main()
{
    std::ios::sync_with_stdio(false);
    
    char x[] = "中";            // Chinese character with unicode point U+4E2D
    char y[] = u8"中";
    wchar_t z = L'中';
    char16_t b = u'\u4e2d';
    char32_t a = U'\U00004e2d';

    std::cout << x << '\n';     // Ok
    std::cout << y << '\n';     // Ok
    std::wcout.imbue(std::locale("en_US.utf8"));
    std::wcout << z << '\n';    // ?? 
    
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
    std::cout << conv32.to_bytes(a) << '\n';

    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> conv16;
    std::cout << conv16.to_bytes(b) << '\n';
}