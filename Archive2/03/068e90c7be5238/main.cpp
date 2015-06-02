#include <iostream>
#include <string>
#include <regex>
#include <locale>
 
 
void display_result(const std::wstring & _str, const std::wregex & _rgx)
{
    if (std::regex_match(_str, _rgx))
        std::wcout << "Positive match found in \"" << _str << "\".\n";
    else
        std::wcout << "NO match found in \"" << _str << "\".\n";
}
 
int main(int argc, char *argv[])
{
   // setlocale(LC_ALL, "");
    std::locale::global(std::locale(""));
 
 
    std::wregex rgx(L"[[:alpha:]]+", std::regex_constants::icase | std::regex_constants::extended | std::regex_constants::collate);
 
    std::cout << "regex use " << rgx.getloc().name() << " locale.\n";
 
 
    std::wstring str{ L"Student" };
 
    display_result(str, rgx);
 
    str = L"Élève";
 
    display_result(str, rgx);
 
    rgx.assign(L"[[=e=]]", std::regex_constants::icase | std::regex_constants::extended | std::regex_constants::collate);
    str = L"E";
 
    display_result(str, rgx);
 
    str = L"É";
 
    display_result(str, rgx);
 
 
    std::cin.get();
}