#include <boost/date_time/gregorian/greg_date.hpp>
#include <iostream>

int main() {
    using boost::gregorian::date;

    date a { 2005, 1, 1 }, b { 2006, 12, 31 };

    std::cout << (b-a).days() << "\n";
}
