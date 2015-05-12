#include <iostream>
#include <utility>
#include <ctime>

using namespace std;

#define SEGS 60
#define MINS 60
#define HOURS 24

int days(tm* date1, tm* date2)
{
    return (mktime(date1) - mktime(date2)) / SEGS / MINS / HOURS;
}

tm mkdate(int day, int mon, int year)
{
    tm date = {0, 0, 0};
    
    date.tm_mday = day;
    date.tm_mon = mon - 1;
    date.tm_year = year - 1900;
    
    return date;
}

int main()
{
    tm date1 = mkdate(31, 12, 2030);
    tm date2 = mkdate(1, 1, 2000);
    
    cout << days(&date1, &date2) << endl;
    // 11322... OK 30 * 365  (1/1/2000 - 1/1/2030) + 8 (leap years) + 364 (from 1/1/2030 - 31/12/2030).
    
    date1 = mkdate(31, 12, 2030);
    date2 = mkdate(1, 1, 1930);
    cout << days(&date1, &date2) << endl;
    // 36889... OK; but in my machine, it returns 36888.
    
    date1 = mkdate(31, 12, 1943);
    date2 = mkdate(1, 1, 1943);
    cout << days(&date1, &date2) << endl;
    // 364... OK: but in my machine, it returns 363.
    
    date1 = mkdate(30, 6, 1943);
    date2 = mkdate(1, 6, 1943);
    cout << days(&date1, &date2) << endl;
    // 29... OK; but in my machine, it returns 28.
    
    date1 = mkdate(27, 6, 1943);
    date2 = mkdate(26, 6, 1943);
    cout << days(&date1, &date2) << endl;
    // 1... OK; but in my machine, it returns 0.
    
    return 0;
}
