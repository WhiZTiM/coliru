#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <boost/foreach.hpp>

int main(){

    std::vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(8);
    
    BOOST_FOREACH(int& element, v)
    {
        element +=10;
    }
    
    BOOST_REVERSE_FOREACH(int element, v)
    {
        std::cout << element << ", ";
    }
    std::cout << std::endl;
    
    std::map<std::string, std::string> content;
    content["I"]   = "am";
    content["you"] = "are";
    content["he"]  = "is";
    content["she"] = "is";
    
    // typedef needed for types contain ',' character
    typedef std::pair<const std::string, std::string> content_element;
    
    BOOST_FOREACH(content_element& element, content)
    {
        element.second += " alive";
    }
    
    BOOST_FOREACH(content_element element, content)
    {
        std::cout << element.first << ": " << element.second << std::endl;
    }
}

