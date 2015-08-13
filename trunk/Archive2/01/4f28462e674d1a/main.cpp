#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> split_string(const std::string & line, char delim = ' ')
{
    std::vector<std::string> sep;
    std::string token;
    std::stringstream ss(line);
    while(getline(ss, token, delim))
        sep.push_back(token);
    return sep;
}

int main ()
{
    std::vector<std::string> sep = split_string("Name|Phone Number|Account Number|Price|Tariff|6079777", '|');
    for(const auto & e : sep)
        std::cout << e << std::endl;
    return 0;
}