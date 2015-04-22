#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    // Simple regular expression matching
    std::string fnames[] = {"ftp://127.0.0.1:8080/", "foo.txt"};


    // Extraction of a sub-match
    std::regex base_regex("([a-z]+)\\://");
    std::smatch base_match;
 
    for (const auto &fname : fnames) {
        if (std::regex_match(fname, base_match, base_regex)) {
            // The first sub_match is the whole string; the next
            // sub_match is the first parenthesized expression.
            if (base_match.size() >= 2) {
                std::ssub_match base_sub_match = base_match[1];
                std::string base = base_sub_match.str();
                std::cout << fname << " -->  " << base <<"\n";
            }
        }
    }   
}