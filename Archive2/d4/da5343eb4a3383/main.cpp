#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time/local_time_io.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

int main() {

    namespace lt = boost::local_time;
    namespace pt = boost::posix_time;
    using   date = boost::gregorian::date;

    lt::tz_database db;
    db.load_from_file("tzdb.csv");

    auto NY = db.time_zone_from_region("America/New_York");
    auto HK = db.time_zone_from_region("Asia/Hong_Kong");

    lt::local_date_time first (date {2015,1,1}, pt::time_duration{10,12,0}, NY, false);
    lt::local_date_time second(date {2015,1,1}, pt::time_duration{10,12,0}, HK, false);

    lt::local_time_period period(first, second);
    std::cout << "period: " << period << "\n";
    std::cout << "duration: " << period.length() << "\n";
}
