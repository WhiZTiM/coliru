#include <iostream>
#include <chrono>

#define d_days 5

int main()
{
    using namespace std::chrono_literals;
    auto day = 24h * d_days;
    auto halfhour = 0.5h;
    std::cout << "one day is " << day.count() << " hours\n"
              << "half an hour is " << halfhour.count() << " hours\n";
}