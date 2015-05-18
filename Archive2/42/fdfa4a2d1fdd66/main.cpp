#include <iostream>
#include <locale>
#include <sstream>
#include <iterator>
#include <ctime>
 
void try_get_date(const std::string& s)
{
    std::cout << "Parsing the date out of '" << s <<
                 "' in the locale " << std::locale().name() << '\n';
    std::istringstream str(s);
    std::ios_base::iostate err = std::ios_base::goodbit;
 
    std::tm t;
    std::istreambuf_iterator<char> ret =
        std::use_facet<std::time_get<char>>(str.getloc()).get_date(
            std::istreambuf_iterator<char>(str),
            std::istreambuf_iterator<char>(),
            str, err, &t
        );
    str.setstate(err);
    if(str) {
        std::cout << "Day: "   << t.tm_mday << ' '
                  << "Month: " << t.tm_mon + 1 << ' '
                  << "Year: "  << t.tm_year + 1900 << '\n';
    } else {
        std::cout << "Parse failed. Unparsed string: ";
        std::copy(ret, std::istreambuf_iterator<char>(),
                  std::ostreambuf_iterator<char>(std::cout));
        std::cout << '\n';
    }
}
int main()
{
    std::locale::global(std::locale("en_US.utf8"));
    try_get_date("02/01/2013");
    try_get_date("02-01-2013");
 
    std::locale::global(std::locale("ja_JP.utf8"));
    try_get_date("2013年02月01日");
}