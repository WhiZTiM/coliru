#include <iostream>
#include <vector>
#include <string>
#include <bitset>

int main()
{
    std::string test = "acaagatgccattgtcccccggcctcctgctgctgctgctctccggggccacggccaccg";
	std::vector<std::bitset<8>> dna;
	std::string builder;
	int counter = 0;
	for (auto e : test)
	{
		switch (e)
		{
		case 'a':
			builder += "00";
			break;
		case 'c':
			builder += "01";
			break;
		case 't':
			builder += "10";
			break;
		case 'g':
			builder += "11";
			break;
		}
		if (++counter % 4 == 0)
		{
			dna.emplace_back(builder);
			builder.clear();
		}
	}
	std::cin.get();
	return 0;
}

