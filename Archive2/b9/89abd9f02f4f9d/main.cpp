#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>

int main()
{
    time_t time_1, time_2;
    std::tm tm1 = {};
    std::tm tm2 = {};
    memset(&tm1, 0, sizeof(std::tm));
    memset(&tm2, 0, sizeof(std::tm));
    
    strptime("1 1 1900 12:43:40", "%d %m %Y %H:%M:%S", &tm1);
    strptime("1 1 1900 11:33:45", "%d %m %Y %H:%M:%S", &tm2);
    
    
    time_1 = mktime(&tm1);
    time_2 = mktime(&tm2);
    
     //   time_1  = difftime(time_2,  time_1);                                                
    std::cout << ctime(&time_1) << std::endl;
    std::cout << asctime(&tm1) << std::endl;
}
