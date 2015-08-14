#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/variant.hpp>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct something
{
    std::string id;
    int index;
    bool enabled;
};

std::ostream& operator<<(std::ostream& os, const something& a_thing)
{
    std::cout << "id: " << a_thing.id << std::endl;
    std::cout << "index: " << a_thing.index << std::endl;
    std::cout << "enabled: " << a_thing.enabled << std::endl;
    
    return os;
}

int main()
{
    typedef boost::variant<std::string*, int*, bool*> val_t;
    std::map<std::string, val_t> val_map;
    
    something a_thing {"", -1, false};
    
    std::cout << a_thing << std::endl;
    
    val_map["id"] = &a_thing.id;
    val_map["index"] = &a_thing.index;
    val_map["enabled"] = &a_thing.enabled;
    
    *boost::get<std::string*>(val_map["id"]) = "jones";
    *boost::get<int*>(val_map["index"]) = 0;
    *boost::get<bool*>(val_map["enabled"]) = true;
    
    
    std::cout << a_thing << std::endl;
}
