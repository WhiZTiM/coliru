#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::string str = "hello jane 7 14 1993 female";
    
    std::string greeting, name, month, day, year, gender;
    std::istringstream(str) >> greeting >> name >> month >> day >> year >> gender;
    
    std::cout << greeting << ' ' << name << ' ' << month << ' ' << day << ' ' << year << ' ' << gender;
}
