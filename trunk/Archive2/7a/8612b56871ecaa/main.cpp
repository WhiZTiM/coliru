#include <iostream>
#include <map>
#include <string>
#include <boost/assign/list_of.hpp>
using boost::assign::map_list_of;

const std::map<int, std::map<int, char> > test = map_list_of
    (100, std::map<int, char>(map_list_of
        (1, 'a')
        (2, 'b')
    ))
    (101, std::map<int, char>(map_list_of
        (1, 'c')
        (2, 'd')
    ))
;

int main()
{
    std::cout << test.find(101)->second.find(2)->second << "\n";
}
