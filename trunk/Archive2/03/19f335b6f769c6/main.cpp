#include <string>
#include <chrono>

#include <boost/date_time.hpp>


auto time_point_from_date_string(std::string const& value) -> std::chrono::system_clock::time_point {
    using namespace boost::gregorian;

    auto tm = to_tm(from_simple_string(value));

    return std::chrono::system_clock::from_time_t(mktime(&tm));
}

auto time_point_to_date_string(std::chrono::system_clock::time_point const& date) -> std::string {
    using namespace boost::gregorian;
    using namespace boost::posix_time;

    auto time = std::chrono::system_clock::to_time_t(date);

    return to_iso_extended_string(date_from_tm(to_tm(from_time_t(time))));
}

int main() {
    auto time_point = time_point_from_date_string("2015-09-27");
    std::cout << time_point_to_date_string(time_point);
}