#include <iostream>
#include <chrono>

class UtcTime {
  public:
    std::chrono::time_point<std::chrono::system_clock> time_point;
    time_t time;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;
    long long epoch;

    UtcTime() {
      time_point = std::chrono::system_clock::now();
      time_t time = std::chrono::system_clock::to_time_t(time_point);
      epoch = std::chrono::duration_cast<std::chrono::microseconds>
              (time_point.time_since_epoch()).count();
      std::tm* times = std::gmtime(&time);
      year = times->tm_year;
      month = times->tm_mon;
      day = times->tm_mday;
      hour = times->tm_hour;
      minute = times->tm_min;
      second = times->tm_sec;
      millisecond = ((epoch % 1000000) /1000);
    }
    double Epoch() { return (double)epoch / 1000000; };
};

int main() {
    UtcTime now;
    std::cout << now.second << " millisecond " << now.millisecond <<std::endl;

}