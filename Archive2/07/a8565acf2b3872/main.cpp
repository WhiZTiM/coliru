#include <iostream>
#include <sstream>
#include <time.h>
#include <string>
#include <boost/filesystem.hpp>
void AddTime(int seconds, tm* date) {
    if (date == NULL) return;
    date->tm_sec += seconds;
    mktime(date);
}

int main (void)
{ 

boost::filesystem::path temp = boost::filesystem::unique_path();
const std::string tempstr    = temp.native();  // optional
std::cerr << tempstr << std::endl;

}