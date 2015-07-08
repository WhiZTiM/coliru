#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int main()
{
    std::string s = "XPOINT:D#{MON 3};S#{1}.";

	std::regex word_regex(R"(\{(.*?)\})");
	auto first = std::sregex_iterator(s.begin(), s.end(), word_regex),
	     last   = std::sregex_iterator();;

	while (first != last)
		std::cout << first++->str() << ' ';
}
