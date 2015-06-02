#include <iostream>
#include <vector>
#include <clocale>
#include <cwchar>
 
void print_as_wide(const char* mbstr)
{
    std::mbstate_t state = std::mbstate_t();
    int len = 1 + std::mbsrtowcs(NULL, &mbstr, 0, &state);
    std::vector<wchar_t> wstr(len);
    std::mbsrtowcs(&wstr[0], &mbstr, wstr.size(), &state);
    std::wcout << "Wide string: " << &wstr[0] << '\n'
               << "The length, including '\\0': " << wstr.size() << '\n';
}
 
int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    const char* mbstr = u8"z\u00df\u6c34\U0001d10b"; // or u8"zß水𝄋"
                        // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    print_as_wide(mbstr);
}