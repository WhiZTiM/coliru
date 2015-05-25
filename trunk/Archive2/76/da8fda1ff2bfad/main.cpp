#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

int main() {
    static const boost::posix_time::ptime epoch { { 1970, 1, 1 }, {} };

    auto now = boost::posix_time::microsec_clock::universal_time();

    std::cout << "Time in milliseconds since 1970: " << (now-epoch).total_milliseconds() << "\n";
}
