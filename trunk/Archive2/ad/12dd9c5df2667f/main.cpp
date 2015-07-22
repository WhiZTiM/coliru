#include <iostream>
int main()
{
    char x[] = "中";            // Chinese character with unicode point U+4E2D
    char y[] = u8"中";
    wchar_t z = L'中';
    char16_t b = u'\u4e2d';
    char32_t a = U'\U00004e2d';

    std::cout << x << '\n';     // Ok
    std::cout << y << '\n';     // Ok
    std::cout << z << '\n';     // prints the decimal number (20013) corresponding to the unicode point U+4E2D
    std::cout << a << '\n';     //             "                    "                   "
    std::cout << b << '\n';     //             "                    "                   "
}
