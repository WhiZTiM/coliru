
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <sstream>
#include <vector>

std::string const formatMask = "%m/%d/%y %r";
//std::string const formatMask = "%m/%d/%y %T";

std::string time_to_str(time_t time)
{
    std::ostringstream strstr;
	strstr << std::put_time(localtime(&time), formatMask.c_str());
	return strstr.str();
}

time_t str_to_time(std::string stime)
{
    std::stringstream strstr(stime);
    strstr.exceptions(std::ios::failbit | std::ios::badbit);
    std::tm tm = std::tm();
    strstr >> std::get_time(&tm, formatMask.c_str());
    return std::mktime(&tm);
}

int main()
{
	time_t time = 1420455540;
	for (int i = 0; i < 20; ++i)
	{
		time_t mytime = time + 60 * 10 * i;
		std::cout << mytime << " " << time_to_str(mytime) << " " << str_to_time(time_to_str(mytime)) << " " << time_to_str(str_to_time(time_to_str(mytime))) << std::endl;
	}
}
