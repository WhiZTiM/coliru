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

template <typename T> 
int func(T param) 
{
    param = param + 1;
    return param;
}


template int func<int>(int param);

//template int func<const int>(int param);

//void func_r1(int param){}
//void func_r1(const int param){}


int main()
{
    int var = 1;
    const int var2 = 1;
    
    std::cout << func(var) << std::endl;
    
    //func(var2);
    
    
    //std::cout << words << std::endl;
}
