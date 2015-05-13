#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> split_words(std::string s)
{
    std::string a = "";
	std::vector<std::string> split;

	for (unsigned int i = 0; i < s.length(); ++i)
	{
		if (s[i] != ' ')
		{
			a += s[i];
		}
		else 
		{
			split.push_back(a);
            a = "";
		}
	}

    split.push_back(a); //das letzte wort hat am ende kein leerzeichen

	for (unsigned int j = 0; j < split.size()-1; ++j)
	{

			std::cout << split[j] << ",";
	}

	std::cout << split[split.size()-1];

	return split;
}

int main()
{
	
	std::cout << "Geben Sie Wörter oder einen Satz ein: ";
    std::string s{"Ich bin ein testsatz"};
	//std::cin >> s;

	split_words(s);

	return 0;
}