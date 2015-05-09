//#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/time_point.hpp>
#include <boost/chrono/io/time_point_io.hpp>
#include <boost/chrono/chrono.hpp>
#include <iostream>

int main() {
    boost::chrono::system_clock::time_point timePoint = boost::chrono::system_clock::now();
    std::cout
        << boost::chrono::time_fmt(boost::chrono::timezone::local)
        << timePoint
        << "\n";
}
