#include<boost/property_tree/json_parser.hpp>
#include<iostream>

int main(){
    using namespace boost::property_tree;

    ptree outer;
    auto& inner = outer.add_child("stations", {});
    inner.put("area CHALLENGE_FUTURE.areaname CHALLENGE_FUTURE", "something");

    write_json(std::cout, outer);
}
