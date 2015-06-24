#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>

//#include  "boost/algorithm/hex.hpp"
#include "boost/format.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
//#include "boost/date_time/local_time/local_time.hpp"
//#include "boost/date_time/time_zone_base.hpp"
//#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time.hpp>
//#include <boost/thread.hpp>
#include <boost/assign/list_of.hpp>
#include "boost/lexical_cast.hpp"
#include <boost/shared_ptr.hpp>
//#include <boost/algorithm/string.hpp>
// #include <boost/regex.hpp>

#define _VARNAME(a) std::string(#a)

void f(const std::string & str)
{
    std::cout << "f : " << str << std::endl;
}

int main()
{
    std::string s = "aa";
    f(s);
    f("bbcde");
    
}