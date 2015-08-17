#include <iostream>
#include <string>
#include <vector>
#include <map>

template<typename Key, typename Value>
inline bool map_contains(const std::map< Key, Value > m, const Key& k)
{
    return m.find(k) != m.end();
}

int main()
{
    std::map<std::string, std::string> M;
    std::cout << map_contains(M, "hello");
}
