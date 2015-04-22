#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    // Simple regular expression matching
    std::string fnames[] = {"ftp://127.0.0.1:8080/", "ftp://127.0.0.1/", 
      "ftp://127.0.0.1/home/amit", "ftp://127.0.0.1:8080/home/amit", "ftp://127.0.0.1",
      "ftp://ftp-app-store.com:8080/home"
    };

    // Extraction of several sub-matches
    std::regex pieces_regex("([a-z]+)\\://(.*)[[\\:]([0-9]+)]?[\\/](.*)");
    std::smatch pieces_match;
 
    for (const auto &fname : fnames) {
        if (std::regex_match(fname, pieces_match, pieces_regex)) {
            std::cout << fname << '\n';
            for (size_t i = 0; i < pieces_match.size(); ++i) {
                std::ssub_match sub_match = pieces_match[i];
                std::string piece = sub_match.str();
                std::cout << "  submatch " << i << ": " << piece << '\n';
            }   
        }   
    }   
}