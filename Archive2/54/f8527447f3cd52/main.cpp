#include <iostream>
#include <sstream>
#include <unordered_set>
#include <string>

// assumes that a word is any sequence of non-white-space characters
// return set of words read from the input stream
std::unordered_set<std::string> words_read_from(std::istream& stm)
{
    std::unordered_set<std::string> words;
	std::string str;
	while (stm >> str) words.insert(str);
	return words;
}

// return true if 'phrase' contains any substring in the set 'substrings'
// note: case-sensitive
bool contains_substring_in(const std::string& phrase, const std::unordered_set<std::string>& substrings)
{
	for (const std::string& str : substrings ) // for each substring 'str' in 'substrings'
	{
		if ( phrase.find(str) != std::string::npos ) // if 'phrase' contains the substring
			return true;
	}
	return false;
}

int main()
{
	std::istringstream txt1("Dadhasapples\n"
		"Momhaspears\n"
		"Grandmahasgrapes\n"
		"Grandpahasnectarines\n"
		"Ihaveoranges\n");

	std::istringstream txt2("pear\ngrap\n" ) ;

	// step 1: get the set of all words in txt2
	const auto words_in_txt2 = words_read_from(txt2);

	// step 2: for each line in txt1
	std::string line;
	while (std::getline(txt1, line))
	{
		// step 2a. check if the line contains any word in the set of words in txt2
		if ( contains_substring_in( line, words_in_txt2 ) ) // if it does
			std::cout << line << '\n'; // print the line
	}
}
