#include <iostream>
#include <string>
#include <vector>
#include <map>

template<typename A, typename B> inline bool map_contains(const std::map< A, B > m, const A& str)
{
    return m.find(str) != m.end();
}

int main()
{
    std::map<int, std::string> M;
    std::cout << map_contains(M, "hello");
}
