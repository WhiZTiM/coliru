#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
   
    std::vector<int> test = {2,4,6,8};
    std::cout << test << "\n";
    
    test.erase(test.begin()+1);
    std::cout << test << "\n";
    
    test.insert(test.begin()+1,3);
    std::cout << test << "\n";
}
