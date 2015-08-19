#include <iostream>
#include <locale>
#include <codecvt>
 
int main()
{
    //std::locale l1;  // l1 is a copy of the classic "C" locale
    std::locale l2("en-US.UTF-8"); // l2 is a unicode locale
    //std::locale l3(l1, l2, std::locale::ctype); // l3 is "C" except for ctype, which is unicode
   // std::locale l4(l1, new std::codecvt_utf8<wchar_t>); // l4 is "C" except for codecvt
    std::cout << "Locale names:\nl1: " << l2.name() << '\n';
}