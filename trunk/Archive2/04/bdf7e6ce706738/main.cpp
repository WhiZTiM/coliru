#include <vector>
#include <sstream>
#include <string>
#include <iostream>

std::vector<int> parseInts(std::string str) {
    std::vector<int> ints;
	std::stringstream ss(str);
	char ch;
	int x = 0;
	do {
		ss >> x >> ch;
		ints.push_back(x);
	} while (x != 0);
	return ints;
}

int main() {
	std::string str;
	std::cin >> str;
	std::vector<int> integers = parseInts(str);
    std::copy(begin(integers), end(integers), std::ostream_iterator(std::cout, "\n"));
	return 0;
}