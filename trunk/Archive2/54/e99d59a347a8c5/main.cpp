#include <boost/iterator.hpp>
#include <boost/algorithm/string.hpp>
#include <iterator>
#include <iostream>

void string_test()
{
    std::string my_str = "Hello, world, it's a wonderful day";

    std::cout << boost::to_upper_copy(my_str) << std::endl; // works, but not a sub-string

    auto const rng2 = boost::make_iterator_range(my_str.begin(), my_str.begin() + 10);
    std::string substr(rng2.begin(), rng2.end());
    boost::to_upper(substr);
    std::cout << substr << std::endl;
    
    std::string result;
    result.reserve(rng2.size());
    boost::to_upper_copy(std::back_inserter(result), rng2);
    std::cout << result << std::endl;
}

int main()
{
  string_test();
}
