#include <set>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

class cvt {
    std::string val;
public:
	cvt(char c) : val(1, c) {}
	cvt(std::string const &s) : val(s) {}
	operator std::string() const { return val; }
	friend bool operator<(std::string const &a, cvt const &b) { return a < b.val; }
};


int main() {
	std::string some_string = "ZABCDECD";
	std::set<cvt> char_set(some_string.begin(), some_string.end());

	std::set<std::string> strings{ "A", "C", "E", "F", "Y" };

	std::set_intersection(char_set.begin(), char_set.end(), strings.begin(), strings.end(),
		std::ostream_iterator<std::string>(std::cout, "\n"));
}
