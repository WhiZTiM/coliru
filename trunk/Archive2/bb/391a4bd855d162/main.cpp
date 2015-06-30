#include <vector>
#include <string>
#include <sstream>
#include <iostream>

std::vector<std::string> tokenize(const std::string& str, const char delimiter, bool collapse_delimiters)
{
    std::vector<std::string> tokens;
	
	std::stringstream ss(str);
	std::string tmp;
	while (std::getline(ss, tmp, delimiter)) {
		if (!tmp.empty() || !collapse_delimiters)
			tokens.push_back(tmp);
	}
	
    // Is this right? I want an empty final token since there is a trailing
    // delimiter, and std::getline won't do that for me.
    if (!collapse_delimiters && !str.empty() && str.back() == delimiter)
        tokens.push_back("");
    
	return tokens;
}

int main()
{
    const std::string str = "0:4:1:335577090:1:1:352452736::";
    std::cout << tokenize(str, ':', false).size() << '\n';     // expecting 9
}