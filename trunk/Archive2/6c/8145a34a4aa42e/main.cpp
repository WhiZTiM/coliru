#include <iostream>

#include "boost/date_time/gregorian/gregorian.hpp"

int main()
{
    std::cout << "Year: " << boost::gregorian::day_clock::universal_day().year() << std::endl;
}
