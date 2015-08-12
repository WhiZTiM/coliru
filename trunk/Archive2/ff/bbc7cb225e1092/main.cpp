#include <string>
#include <iostream>
#include <map>
 
int main()
{
    typedef std::map<std::string,int>  mapT;
 
    mapT my_map;
    my_map["first"]=  11;
    my_map["second"]= 23;
 
    mapT::iterator  it= my_map.find("first");
    if( it != my_map.end() ) std::cout << "A: " << it->second << "\n";
 
    it= my_map.find("third");
    if( it != my_map.end() ) std::cout << "B: " << it->second << "\n";
 
    // Accessing a non-existing element creates it
    if( my_map["third"] == 42 ) std::cout << "Oha!\n";
 
    it= my_map.find("third");
    if( it != my_map.end() ) std::cout << "C: " << it->second << "\n";
 
    return 0;
}