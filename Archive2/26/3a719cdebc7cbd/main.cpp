#include <string>
#include <vector>
#include <iostream>

std::string s;

std::vector<std::string> split_words(std::string s)
{
    std::string a;
	std::vector<std::string> split;
	
	for (int i = s.size()-1; i>=0 ;i--)
	{
		if (s[i]!= ' ')
		{
			a[i] = s[i];
			s.pop_back();
		}
		else 
		{
			split.push_back(a);
			s.pop_back();
		}
	}

	for (int j = 0; j< split.size()-1; j++)
	{

			std::cout << split[j] << ",";
	}

	std::cout << split[split.size()-1];

	return split;
}

int main()
{
	
	std::cout << "Geben Sie Wörter oder einen Satz ein: ";
	std::cin >> s;

	 split_words(s);

	return 0;
}