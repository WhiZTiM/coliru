#include <locale>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


int main(int argc, char* argv[])
{
    
    std::string json = R"ololo( 
    {
  "instruments": 
      {
        "minShift": true,
        "maxShift": 1,
        "stepShift": false,
        "instrument_old": "CFH/EURUSD",
        "instrument_new": "LMAX/EURUSD"
      } 

})ololo";
    std::istringstream json_is(json);
    boost::property_tree::ptree ptree;
    boost::property_tree::read_json(json_is, ptree);
    std::cerr << ptree.get<std::string>("instruments.instrument_old","lol") <<std::endl;
}