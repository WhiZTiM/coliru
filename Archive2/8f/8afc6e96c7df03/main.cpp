#include <ctime>
#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>
#include <string.h>

int main()
{
    std::tm theTime = {};
    // zero out theTime following recommendation here: 
    // http://en.cppreference.com/w/cpp/io/manip/get_time:  
    //          portable programs should initialize every field ... to zero before calling std::get_time
    memset(&theTime, 0, sizeof(std::tm));
    
    // initialize timeToConvert with the Year-Month-Day Hours:Minutes:Seconds string you want
    std::string timeToConvert = "2015-07-18 00:00:00";
    std::istringstream timeStream(timeToConvert);
    
    // need to use your locale (en-US)
    timeStream.imbue(std::locale("en_US.UTF-8"));
    timeStream >> std::get_time(&theTime, "%Y-%m-%d %H:%M:%S");
    if (timeStream.fail()) 
    {
        std::cerr << "Parse failed\n";
        exit(0);
    } 
    
    // call mktime to fill out other files in theTime
    std::mktime(&theTime);
    
    
    // get years since 1900
    int year = theTime.tm_year + 1900;
    
    /* determine if year is leap year:
    If the year is evenly divisible by 4, go to step 2. ...
    If the year is evenly divisible by 100, go to step 3. ...
    If the year is evenly divisible by 400, go to step 4. ...
    The year is a leap year (it has 366 days).
    The year is not a leap year (it has 365 days).
    */
    bool isLeapYear =  year % 4 == 0 &&
                        year % 100 == 0 &&
                        year % 400 == 0;
    
    // get number of days since January 1st
    int days = theTime.tm_yday+1; // Let January 1st be the 1st day of year, not 0th
  
    
    // get number of days in this year (either 365 or 366 if leap year)
    int daysInYear = isLeapYear ? 366 : 365;
    
    
    double yearAsFloat = static_cast<double>(year) + static_cast<double>(days)/static_cast<double>(daysInYear);
    
    std::cout << timeToConvert << " is " << yearAsFloat << std::endl;
}