#include <iostream>
#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using namespace boost::property_tree;

int main()
{
        std::string ss = "{ \"id\" : \"abc123\", \"number\" : \"0123456789\", \"somelist\" : [{ \"timestamp\" : \"May 1, 2015\" , \"data\" : { \"description\" : \"some description\", \"value\" : \"100.000000\" } }, {\"a\": 1}] }";

        ptree pt2;
        std::istringstream is(ss);
        read_json(is, pt2);
        std::string _id = pt2.get<std::string>("id");
        std::string _number = pt2.get<std::string>("number");
        std::string _list = pt2.get<std::string>("somelist"); 


        for(auto const& node : pt2.get_child("somelist"))
            write_json(std::cout, node.second);
        
        return 0;
}