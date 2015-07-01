#include <iostream>
#include <regex>

int main()
{
    std::regex log_line_regex_(".+?\\s(.+)");

    char const *log_line = "06-29 18:20:08.938 1031 1099 D WifiStateMachine: processMsgConnect oo ModeState";

    std::smatch matches;
    
    std::string input(log_line);
    if (regex_match(input, matches, log_line_regex_))
    {
        std::cout << "match: " << log_line << std::endl;

        for (unsigned i = 0; i < matches.size(); i++) {
            std::cout << "$" << i << ": " << std::string(matches[i].first, matches[i].second) << std::endl;
        }
    }
}
