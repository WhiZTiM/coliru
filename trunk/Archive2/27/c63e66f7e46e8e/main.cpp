#include <iostream>
#include <chrono>
 
int main()
{
    using namespace std::chrono_literals;
     std::chrono::minutes lesson = 1min + 61s;
    auto halfmin = 0.5min;
    std::cout << "one lesson is " << lesson.count() << " minutes\n"
              << "half a minute is " << halfmin.count() << " minutes\n";
}