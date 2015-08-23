#include <iostream> // std_lib_facilities.h
#include <string>

int main()
{
    std::cout << "Please put your birthday in mm/dd/yyyy \n";

	int month;
	int day;
	int year;
	char slash ; // to read the separator

	std::cin >> month; // read the month
	std::cin >> slash; // read the '/'
	std::cin >> day; // read the day
	std::cin >> slash; // read the '/'
	std::cin >> year; // read the year

	std::string month_name = "invalid month" ;

	// if the condition ( month === 1 ) evaluates to true (if the entered month is 1)
	if( month == 1 ) month_name = "January"; // then set month_name to "January";

	if( month == 2 ) month_name = "February";
	// and so on, up to December

    std::cout << "Your birthday is: " << month_name << ' ' << day << ", " << year << '\n' ;
}
