#include <array>

//std::array is copyable, so you can return it by value!
std::array<int,2> retarray() { return {1,2}; }

//int[2] retcarrray() { return ???; }

//you can also return and accept references to std::arrays...
std::array<int,2>& modarray(std::array<int,2>& arr) { arr[0]+=1; return arr; }

//...without hurting yourself
int (&modcarray(int (& arr)[2]))[2] { arr[0]+=1; return arr; }

int main()
{
    std::array<int,2> arr{1,2};
    int carr[2] = {1,2};
    
    arr = retarray();
    
    modarray(arr);
    modcarray(carr);
    
    //std array knows its size!
    arr.size();
}

//std::array is awesome!