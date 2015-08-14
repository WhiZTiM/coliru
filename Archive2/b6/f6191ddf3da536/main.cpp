#include <iostream>
#include <map>

template <typename T1, typename T2>
T2 mapGetByKey(std::map<T1, T2>& map, T1 key, T2 defaultValue = {})
{
    auto it = map.find(key);

    if (it != map.end())
    {
        return it->second;
    }

    return defaultValue;
}

template <typename T1>
const char* mapGetByKey(std::map<T1, const char*>& map, const T1& key)
{
    return mapGetByKey(map, key, "default string");
}

int main()
{
    std::map<int, int> i;
    std::map<int, const char*> c;
    
    std::cout << mapGetByKey(i, 0xCAFE) << std::endl;
    std::cout << mapGetByKey(c, 0xBEEF) << std::endl;
}
