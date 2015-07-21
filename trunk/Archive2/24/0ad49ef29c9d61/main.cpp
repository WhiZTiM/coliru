#include <iostream>
#include <set>
#include <utility>
#include <ctime>

using namespace std;

int main()
{
    tm time {50, 50, 12, 21, 7, 2015 - 1900};
    time_t epoch = mktime(&time);
    printf("%s", asctime(gmtime(&epoch)));         
}