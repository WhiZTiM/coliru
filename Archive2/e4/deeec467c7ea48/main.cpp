#include <iostream>
#include <map>

template <typename T>
T defaultValue()
{
    return {};
}

template <>
const char* defaultValue<const char*>()
{
    return "default string";
}

template <typename T1, typename T2>
T2 mapGetByKey(std::map<T1, T2>& map, const T1& key)
{
    auto it = map.find(key);

    if (it != map.end())
    {
        return it->second;
    }

    return defaultValue<T2>();
}

int main()
{
    std::map<int, int> i;
    std::map<int, const char*> c;
    
    std::cout << mapGetByKey(i, 0xCAFE) << std::endl;
    std::cout << mapGetByKey(c, 0xBEEF) << std::endl;
}
