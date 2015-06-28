#include <regex>
#include <iterator>
#include <iostream>
#include <string>
 
int main()
{
    const std::string s = "what am i trying to find here? is name = value right";
 
    std::regex nv_regex("(((?!=)\\S)+)\\s*=\\s*(\\S+)");
    auto words_begin = 
        std::sregex_iterator(s.begin(), s.end(), nv_regex);
    auto words_end = std::sregex_iterator();
 
    std::cout << "Found " 
              << std::distance(words_begin, words_end) 
              << " words:\n";
 
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;                                                 

        for(auto& smitr : match)
        {
           std::cout << smitr << '\n';
        }
    }   
}