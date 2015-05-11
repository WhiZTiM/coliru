#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time/local_time_io.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

int main() {

    namespace lt = boost::local_time;
    namespace pt = boost::posix_time;

    lt::tz_database db;
    db.load_from_file("tzdb.csv");

    auto NY = db.time_zone_from_region("America/New_York");
    auto HK = db.time_zone_from_region("Asia/Hong_Kong");

    auto first  = lt::local_sec_clock::local_time(NY);
    auto second = lt::local_sec_clock::local_time(HK);

    {
        lt::local_time_period period(first, second);
        std::cout << "period: "   << period          << "\n";
        std::cout << "duration: " << period.length() << "\n";
    }

    first  = lt::local_date_time(first.date(),  pt::hours(7) +  pt::seconds(59), first.zone(),  first.is_dst());
    second = lt::local_date_time(second.date(), pt::time_duration(7, 0, 59),     second.zone(), second.is_dst());

    {
        lt::local_time_period period(first, second);
        std::cout << "period: "   << period          << "\n";
        std::cout << "duration: " << period.length() << "\n";
    }

}
