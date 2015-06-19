#include <iostream>
#include <map>

int main()
{
    std::map<int, int> v;
    v[-10] = 10;
    v[-20] = 20;
    v[-30] = 30;
    v[-40] = 40;
    v[-50] = 50;

    for(auto &i : v)
        std::cout << i.first << " -> " << i.second << std::endl;

    return 0;
}