#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/local_time/local_time_io.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

int main() {
    namespace lt = boost::local_time;
    namespace pt = boost::posix_time;
    using   date = boost::gregorian::date;

    lt::tz_database db;
    db.load_from_file("tzdb.csv");

    //for (auto region : db.region_list()) std::cout << region << "\n";

    auto NY = db.time_zone_from_region("America/New_York");

    date const d1(2015, 11, 1);

    lt::local_date_time nov1_00(d1, pt::hours(0),  NY, true);
    lt::local_date_time nov1_23(d1, pt::hours(23), NY, false);

    lt::local_time_period period(nov1_00, nov1_23);

    std::cout << "period: "   << period          << "\n";
    std::cout << "duration: " << period.length() << "\n";

    // if you insist:
    auto seconds = (nov1_23 - nov1_00).total_seconds();
    std::cout << "seconds: " << seconds << "\n";
}
