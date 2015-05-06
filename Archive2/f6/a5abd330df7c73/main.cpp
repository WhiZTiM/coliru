#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template <typename Ret>
class JFunction
{
public:

    template <typename std::enable_if<std::is_void<Ret>::value>::type* = 0>
    Ret operator()()
    {
        std::cout << "Not returning." << std::endl;
    }
    
    template <typename std::enable_if<!std::is_void<Ret>::value>::type* = 0>
    Ret operator()()
    {
        std::cout << "Returning." << std::endl;
        Ret result;
        return result;
    }
};

int main()
{
    JFunction<int> fInt;
    JFunction<void> fVoid;
    
    fInt();
    fVoid();
}