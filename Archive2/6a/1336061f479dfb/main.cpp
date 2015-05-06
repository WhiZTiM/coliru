#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template <typename Ret>
class JFunction
{
public:

    template <typename T = Ret>
    typename std::enable_if<std::is_void<T>::value, T>::type
    operator()()
    {
        std::cout << "Not returning." << std::endl;
    }
    
    template <typename T = Ret>
    typename std::enable_if<!std::is_void<T>::value, T>::type
    operator()()
    {
        std::cout << "Returning." << std::endl;
        T result;
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