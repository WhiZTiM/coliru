#include <iostream>
#include <sstream>

void parse(std::string const& s)
{
    std::istringstream text(s);
    text.imbue(std::locale::classic());
    double result;
    text >> result;
    bool ok = text && text.eof();
    std::cout << std::boolalpha << ok << " " << result << std::endl;
}

int main() {
    parse("hello");
    parse("1.23");
    parse("1,23");
    parse("");
}