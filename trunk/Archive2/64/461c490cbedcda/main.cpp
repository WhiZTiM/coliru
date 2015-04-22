#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    // Simple regular expression matching
    std::string fnames[] = {"ftp://127.0.0.1", "ftp://:8080/",  
        "ftp://127.0.0.1/", 
        "ftp://ftp-aricent.com:8080/home", "ftp://ftp-aricent.com/home",
        "http://127.0.0.1:8080/home", "http://127.0.0.1/home", 
        "ftp://127.0.0.1", "ftp://127.0.0.1:8080", "ftp://ftp-aricent.com/", "ftp://ftp-aricent.com:8080/",
        "127", "ftp", "ftp://127.0.0.1:8080/home/amit", "ftp://upload.cisco.com/home/amit"
    };

    // Extraction of several sub-matches
    std::regex pieces_regex("([a-z]*[A-Z]*)\\://([\\w*-\\.*]+):*([0-9]*)/*([\\w*/*.*]*)");
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