#include <iostream>
#include <regex>
#include <string>
int main()
{
   std::string text = "Quick brown fox";
   std::regex vowel_re("/u*/");
   std::cout << std::regex_match(text, vowel_re, "[$&]") << '\n';
}