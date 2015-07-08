#include <iostream>
#include <memory>
#include <ctime>
#include <cstring>

int main()
{
    std::string date = "Thu, 29 Nov 1973 21:33:09 GMT";
    std::tm tm;
    char day[4];
    char month[4];
    std::memset(&tm, 0, sizeof(tm));
    std::memset(day, 0, sizeof(day));
    std::memset(month, 0, sizeof(month));
    const int assigned = std::sscanf(date.c_str(),
    "%3[FMSTWadehinortu], %2u %3[ADFJMNOSabceglnoprtuvy] %4u %2u:%2u:%2u GMT",
    day, reinterpret_cast<unsigned int*>(&tm.tm_mday), month, reinterpret_cast<unsigned int*>(&tm.tm_year),
    reinterpret_cast<unsigned int*>(&tm.tm_hour), reinterpret_cast<unsigned int*>(&tm.tm_min),
    reinterpret_cast<unsigned int*>(&tm.tm_sec));
    if (assigned != 7) {
          throw std::invalid_argument("Failed to interpret date string as HTTP timestamp: " + date);
    }
    std::cout << "day: " << day << std::endl;
    std::cout << "month: " << month << std::endl;
    char time[1024];
    std::strftime(time, 1023, "%c", &tm);
    std::cout << "time: " << time << std::endl;
}
