#include <iostream>
#include <locale>
#include <codecvt>
#include <vector>
#include <string>
#include <algorithm>

 
int main()
{
    std::locale l1;  // l1 is a copy of the classic "C" locale
    std::locale l2("en_US.UTF-8"); // l2 is a unicode locale
    std::locale l3(l1, l2, std::locale::ctype); // l3 is "C" except for ctype, which is unicode
    std::locale l4(l1, new std::codecvt_utf8<wchar_t>); // l4 is "C" except for codecvt
    std::cout << "Locale names:\nl1: " << l1.name() << "\nl2: " << l2.name()
               << "\nl3: " << l3.name() << "\nl4: " << l4.name() << '\n';
               
    std::string s[] = {"c", "X", "b", "Y", "a", "Z"};
	std::vector<std::string> v(s, s+6);
	
    std::sort(v.begin(), v.end());
    for (auto&& s : v) { std::cout << s << ' '; }
    
    std::cout<< '\n';
	std::locale en_us{"en_US"};
	std::sort(v.begin(), v.end());
	for (auto&& s : v) { std::cout << s << ' '; }
}