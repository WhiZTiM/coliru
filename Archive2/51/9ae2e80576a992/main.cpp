#include <ctime>
#include <iomanip>
#include <iostream>

inline const int EST_diff(const bool is_DST)
{
    if (is_DST < 0)
        std::cout << "Erorr! No DST Information available!" << std::endl;    
    
    if (is_DST)
        return 4;
    else
        return 5;
}

inline const bool try_rollback(int& time)
{
    if (time > 1)
    {
        time -= 1;
        return true;
    }
    else
        return false;
}

inline int leapyear(const std::tm *const time)
{
    return time->tm_year % 4 == 0 ? 1 : 0;
}

inline int back_one(int& time, const int increment)
{
    return time = time > 1 ? time - 1 : time + increment - 1;
}

inline int advance_hours(int& time, const int difference)
{
    return time += 24 - difference;
}

inline int days_in_month(const int month, const bool leapyear)
{
    switch(month)
    {
    case 0: //january
        return 31;
    case 1: //february
        return leapyear ? 29 : 28;
    case 2: //march
        return 31;
    case 3: //april
        return 30;
    case 4: //may
        return 31;
    case 5: //june
        return 30;
    case 6: //july
        return 31;
    case 7: //august
        return 31;
    case 8: //september
        return 30;
    case 9: //october
        return 31;
    case 10:    //november
        return 30;
    case 11:    //december
        return 31;
    default:
        std::cout << "Input error in days_in_month!" << std::endl;
        break;
    }
    
    return -1;
}

inline std::tm* rollback_week(std::tm *const time)
{
    back_one(time->tm_wday, 7);
    advance_hours(time->tm_hour, EST_diff(time->tm_isdst));
    return time;
}

inline std::tm* rollback_month(std::tm *const time)
{
    back_one(time->tm_mon, 12);
    back_one(time->tm_mday, days_in_month(time->tm_mon, leapyear(time)));
    return rollback_week(time);
}

inline std::tm* rollback_year(std::tm *const time)
{
    time->tm_year -= 1;
    time->tm_yday += 364 + leapyear(time);
    return rollback_month(time);
}

inline std::tm* UTC_to_EST(std::tm *const time)
{
    if (time->tm_hour > EST_diff(time->tm_isdst))
        time->tm_hour -= EST_diff(time->tm_isdst);
    else
    {
        if (!try_rollback(time->tm_yday))
            rollback_year(time);
        else if(!try_rollback(time->tm_mday))
            rollback_month(time);
        else if(!try_rollback(time->tm_wday))
            rollback_week(time);
    }
    return time;
}

int main()
{
    std::time_t t = std::time(NULL);
    std::tm* time(std::gmtime(&t));
    std::cout << "UTC: " << std::put_time(time, "%c %Z") << '\n';
    std::cout << "EST: " << std::put_time(UTC_to_EST(time), "%c %Z") << '\n';
    std::cout << "Daylight Savings Time is " << (std::gmtime(&t)->tm_isdst < 0 ? "invalid" : (std::gmtime(&t)->tm_isdst > 0 ? "active" : "inactive")) << std::endl;
}