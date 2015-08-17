#include <iostream>
#include <map>

template <typename T>
struct identity { typedef T type; };

template <typename A, typename B>
inline bool contains(const std::map<A, B>& m
                   , const typename identity<A>::type& str)
{
    return m.find(str) != m.end();
}

int main()
{
    std::map<std::string, int> m;
    m["foo"] = 0xCAFE;
    std::cout << contains(m, "foo");
}
