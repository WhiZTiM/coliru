#include <iostream>
#include <string>
#include <vector>
#include <regex>


int main()
{
      auto version = {
        "2012.12",         // "2012", "12", "", ""
        "2012.12-1",       // "2012", "12", "", "1" 
        "2012.12-SP1",     // "2012", "12", "SP1", "" 
        "2012.12-SP2-1",   // "2012", "12", "SP2", "1" 
        "I-2013.12-2",     // "2013", "12", "", "2"
        "J-2014.09",       // "2014", "09", "", ""
        "J-2014.09-SP2-1", // "2014", "09", "SP2", "1"
    };

    //                      J   -  2014       .  09      -  SP2      -  1  
    std::regex regexExpr("[A-Z]?-?([0-9]{4})\\.([0-9]{2})-?(SP[1-9])?-?([1-9])?.*");
    std::smatch pieces_match;

    for (std::string s : version) {
        std::cout << "-----------------------------" << std::endl;
        std::cout << "String to match : " << s << std::endl;
        std::cout << "-----------------------------" << std::endl;

        if (std::regex_match(s, pieces_match, regexExpr)) {
               for (size_t i = 1; i < pieces_match.size(); ++i) {
                std::ssub_match sub_match = pieces_match[i];
                std::string piece = sub_match.str();
                std::cout << "  submatch " << i << ": " << piece << std::endl;
            }
        }
    }

    return 0;
}
