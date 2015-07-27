#include <iostream>
#include <string> // <cstdlib>
#include <fstream>
#include <iomanip>

// using namespace std;

int main()
{
    const char* const path_to_datafile = "payroll.dat" ;

    // create file payroll.dat //// you won't need this ///////////////
    { std::ofstream(path_to_datafile) << "Athos 20.5 7\n" "Aramis 46.8 32\n" "Porthos 25 19\n" ; }
    ////////////// you won't need this ///////////////

    // open the file for input
    std::ifstream data_in(path_to_datafile);

	std::string name ;
	double hourly_wage ;
	int hours_worked ;
	int record_count = 0 ;

	std::cout << std::fixed << std::setprecision(2) ;
	const int NAME_FLD_WIDTH = 8 ; // adjust these as required
	const int WAGE_FLD_WIDTH = 6 ;
	const int HOURS_FLD_WIDTH = 4 ;
	const int PAYCHECK_FLD_WIDTH = 9 ;

	// read data from file 3-tuple by 3-tuple till eof
	while( data_in >> name >> hourly_wage >> hours_worked )
    {
        ++record_count ;
	    const double paycheck = hourly_wage * hours_worked ;
        std::cout << record_count << '.'
                  << std::setw(NAME_FLD_WIDTH) << name
                  << std::setw(WAGE_FLD_WIDTH) << hourly_wage
                  << std::setw(HOURS_FLD_WIDTH) << hours_worked
                  << std::setw(PAYCHECK_FLD_WIDTH) << paycheck << '\n' ;
    }

    std::cout << '\n' << record_count << " records were read\n" ;
}
