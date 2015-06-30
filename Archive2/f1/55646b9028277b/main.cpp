#include <utility>
#include <iostream>

template<typename T>
T pair()
{
    return T();
}

template<typename T, typename U, typename...K>
auto pair()
{
    return std::pair<T, decltype(pair<U,K...>())>();
}


int main(int argc, char **argv)
{
    std::pair<int, int> m2 = pair<int, int>();
    std::pair<int, std::pair<int, int>> m3 = pair<int, int, int>(); 
    std::pair<int, std::pair<int, std::pair<int, int>>> m4 = pair<int, int, int, int>();    // <- Compile Error here [fixed]
    std::cout << "It works" << std::endl;
    return 0;
}
