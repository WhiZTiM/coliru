#include<boost/property_tree/json_parser.hpp>
#include<iostream>

int main(){
    using namespace boost::property_tree;

    ptree inner;
    inner.put("area CHALLENGE_FUTURE.areaname CHALLENGE_FUTURE", "something");

    std::ostringstream inner_json;
    write_json(inner_json, inner);

    ptree outer;
    outer.put("stations", inner_json.str());

    write_json(std::cout, outer);
}
