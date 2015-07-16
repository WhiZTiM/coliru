#include <map>
#include <iostream>
#include "boost/assign.hpp"

template<typename Key, typename T>
T convert(const Key &k, const T &d, const std::map<Key, T> &m) {
    typename std::map<Key, T>::const_iterator it = m.find(k);
    return it == m.end() ? d : it->second;
}

enum MUSIC { ROCK, RAP, EDM, COUNTRY };
enum COLOR { RED, BLUE, ORANGE, WHITE };

int main()
{
    COLOR c = convert<MUSIC, COLOR>(COUNTRY, WHITE,
        boost::assign::map_list_of (RAP, RED) (EDM, BLUE) (ROCK, RED));
    std::cout << c << std::endl;
    COLOR d = convert(COUNTRY, WHITE, {{RAP, RED},{EDM, BLUE},{ROCK, RED}});
    std::cout << d << std::endl;
}