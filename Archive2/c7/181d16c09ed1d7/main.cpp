#include <iostream>
#include <string>
#include <vector>
#include <map>

template<typename Key, typename Value, typename Arg>
inline bool map_contains(const std::map< Key, Value > m, const Arg& value)
{
    return m.find(value) != m.end();
}

int main()
{
    std::map<std::string, std::string> M;
    std::cout << map_contains(M, "hello");
}
