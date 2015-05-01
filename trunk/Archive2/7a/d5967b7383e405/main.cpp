#include <iostream>
#include <map>
#include <string>
#include <boost/assign/list_of.hpp>
using boost::assign::map_list_of;

const std::map<int, std::map<int, std::string> > test =
    map_list_of
        (1, map_list_of
            (1, "bla")
            (2, "blie")
            .convert_to_container<std::map<int, std::string> >()
        )
        (3, map_list_of
            (1, "ha")
            (2, "hie")
            .convert_to_container<std::map<int, std::string> >()
        )
    ;

int main()
{
    std::cout << test.find(3)->second.find(2)->second << "\n";
}