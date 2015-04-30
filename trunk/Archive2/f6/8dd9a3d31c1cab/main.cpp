#include <iostream>
#include <string>
#include <vector>
#include <tuple>

template <typename... Args>
void Deserialize(std::vector<uint8_t> payload, std::tuple<Args...>& output)
{
    for (int i = 0; i < sizeof...(Args); i++)
    {
        std::cout << i << '\n';
    }
}




int main()
{
    std::vector<uint8_t> payload = {1,2,3,4};
    std::tuple<int,uint8_t,std::string> res; 
    Deserialize(payload, res);
}
