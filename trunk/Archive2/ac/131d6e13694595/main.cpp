#include <regex>
#include <locale>
#include <iostream>
#include <codecvt>

int main()
{
    std::string input = u8"aoe\u2028eoa";
    //input = u8"aoeeoa";
    
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf32_conv;
    std::wstring wide_input = utf32_conv.from_bytes(input);
    static_assert(sizeof(wchar_t) == 4, "Must be on UTF-32 system.");
    
    std::wregex no_newlines(L".*");
    
    std::cout << std::boolalpha << std::regex_match(wide_input, no_newlines) << '\n';

    return 0;
}
