// mailtest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>

int validator(std::ifstream file) // file is supposed to be listf from _tmain
{
    std::string entry;
	getline(file, entry);

	std::regex validate("^(([a-zA-Z]|[0-9])|([-]|[_]|[.]))+[@](([a-zA-Z0-9])|([-])){2,63}(([.a-zA-Z0-9]){2,63})+:.*");

	if (std::regex_match(entry, validate)) {
		std::cout << entry << " is a valid format\n";
		return 0;
	}
	else {
		std::cout << entry << " is NOT a valid format\n";
		return 1;
	}
}

int _tmain(int argc, char* argv[])
{
	std::ifstream listf;
	listf.open(argv[1], std::ios::in);

	// Unit test to verify file opens and reads properly.
	std::cout << "Press any key to print the file to the console.\n";
	std::cout << "This is a unit test. report any errors to the project leader.\n";
	std::cin.get();
	if (listf.is_open()) {
		std::string entry;
		while (getline(listf, entry))
		{
			std::cout << entry << '\n';
		}
	}
	else std::cout << "Error: unable to open file\n";
	std::cout << "Press any key to continue to the next step.\n";
	std::cin.get();
	// End of unit test.
	validator(listf); // cannot convert std::ifstream to std::ifstream
	return 0;
}