#include <algorithm>
#include <cctype>
#include <cstddef>
#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace palindrome {

    typedef std::pair<std::size_t, std::size_t> substrings;
	static const char char_offset = 97;
	
	// remove all whitespace and punctuation...
	std::string strip_nonalphanumeric(const std::string& s)
	{
		std::string alphanumericString;
	
		for(std::size_t i = 0, end = s.length(); i < end; ++i)
		{
			if(std::isalpha(s[i]) || std::isdigit(s[i]))
			{
				alphanumericString.append(1, std::tolower(s[i]));
			}
		}
		
		return alphanumericString;
	}
	
	// returns true if it's a palindrome false otherwise.
	bool is_valid(const std::string& s)
	{
		const std::size_t length = s.length();
		
		for(std::size_t i = 0, end = length / 2; i < end; ++i)
		{
			if(s[i] != s[length - i - 1])
			{
				return false;
			}
		}
		
		return true;
	}

	// walk the input string annotating the graph with visits,
	// this informs us which sub-strings we need to test 
	std::deque<substrings> annotate_graph(const std::string& s)
	{
		std::deque<substrings> substringsToCheck;
		std::vector<std::deque<std::size_t> > annotations(26);
		
		for(std::size_t i = 0, end = s.length(); i < end; ++i)
		{
			const char vertex = s[i];

			// skip non-alphanumeric...
			if(!std::isalpha(vertex) && !std::isdigit(vertex))
			{
				continue;
			}

			const char vertex_index = vertex - char_offset;

			// see if we've visited this vertice before...
			if(! annotations[vertex_index].empty())
			{
				std::for_each(annotations[vertex_index].begin(), annotations[vertex_index].end(), [&substringsToCheck, i](const std::size_t start)
				{
					substringsToCheck.push_back(std::make_pair(start, i));
				});
			}
			
			// mark this vertex as visited...
			annotations[vertex_index].push_back(i);
		}
		
		return substringsToCheck;
	}	
}


void usage(char const * const programName)
{
	std::cerr << programName << " <string>" << std::endl;
}


int main(int argc, char** argv)
{
	if(argc < 2)
	{
		usage(argv[0]);
		return -1;
	}

	std::string input = palindrome::strip_nonalphanumeric(argv[1]);

	std::string longestPalindrome;
	std::size_t longestPalindromeLength = 0;
	
	auto substringsToCheck = palindrome::annotate_graph(input);
	
	std::for_each(substringsToCheck.begin(), substringsToCheck.end(), [&](const palindrome::substrings& range)
	{
		auto testString = input.substr(range.first, 1 + range.second - range.first);
		
		if(palindrome::is_valid(testString) && (testString.length() > longestPalindromeLength))
		{
			longestPalindrome = testString;
			longestPalindromeLength = testString.length();
		}
	});
	
	std::cout << longestPalindrome << "\n" << "Length: " << longestPalindromeLength << std::endl;
	return 0;
}
