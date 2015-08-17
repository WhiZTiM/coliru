#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>

size_t find_nth(const std::string & line, const std::string & symbol, size_t nth)
{
	size_t pos = 0;
	size_t counter = 0;
	while (counter < nth && (pos = line.find(symbol, pos)) != std::string::npos)
	{
		counter++; // found a match so increment
		pos++;  // increment so we search for the next one
	}
	return pos;
}       

int main(int argc, char *argv[]) {
    std::cout << find_nth("012#txt1#txt2#txt3#txt4#  #some other text:", "#", 5);
    return 0;
}