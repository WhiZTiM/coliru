#include <iostream>
#include <string>
#include <codecvt>
#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;
int main()
{
    std::string str = "\\u8f93\\u5165\\u7684";
    std::u16string u16;
    qi::parse(str.begin(), str.end(), *("\\u" >> qi::hex), u16);
    std::string u8 = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>().to_bytes(u16);
    std::cout << "utf 8 string " << u8 << " consiting of " << u8.size() << " bytes\n";
}
