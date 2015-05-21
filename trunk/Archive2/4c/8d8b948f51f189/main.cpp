#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;
static qi::int_parser<int, 10, 2, 2> two_digits;

int main() {
    std::string const s = "P112233";

    std::vector<int> nums;
    if (qi::parse(s.begin(), s.end(), "P" >> *two_digits, nums))
    {
        std::cout << "Parsed " << nums.size() << " pairs of digits:\n";
        for(auto i : nums)
            std::cout << " * " << i << "\n";
    }
}
