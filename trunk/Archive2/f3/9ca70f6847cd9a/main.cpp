#include <iostream>                                                                                                 
#include <string>                                                                                                   
#include <vector>                                                                                                   
#include <fstream>                                                                                                  

#include <boost/property_tree/json_parser.hpp>                                                                      
#include <boost/property_tree/ptree.hpp>                                                                            

using namespace std;                                                                                                
using boost::property_tree::ptree;                                                                                  
using boost::property_tree::basic_ptree;                                                                            

int main()                                                                                                          
{                                                                                                                   

    std::string ss = "{ \"id\" : \"abc123\", \"number\" : \"0123456789\", \"somelist\" : [{ \"timestamp\" : \"May 1\
   , 2015\" , \"data\" : { \"description\" : \"some description\", \"value\" : \"100.000000\" } }] }";                 

    ptree pt2;                                                                                                      
    std::istringstream is(ss);                                                                                      
    read_json(is, pt2); 
    std::string _id = pt2.get<std::string>("id");                                                                   
    std::string _number = pt2.get<std::string>("number");                                                           
    std::string _list = pt2.get<std::string>("somelist");                                                           

    for (auto &e : pt2.get_child("somelist"))                                                                       
    {                                                                                                               
        std::cout << "timestamp: " << e.second.get<std::string>("timestamp") << "\n";                               
        ptree d = e.second.get_child("data");                                                                       
        std::stringstream s1;                                                                                       
        boost::property_tree::json_parser::write_json(s1, d);                                                       
        std::cout << s1.str() << std::endl;                                                                         
    }                                                                                                               
    return 0;                                                                                                       
}                                                                                                                   
    