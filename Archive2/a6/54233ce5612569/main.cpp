#include <iostream>

template<typename ret, typename... args> 
class EATEntry{}; // primary

template<typename ret, typename... args> 
class EATEntry<ret(args...)> // specialization 
{
public:
    EATEntry()
    {
        std::cout << "EATEntry<ret(args...)>" << std::endl;
    }
}; 

int CreateThread(int, int, bool){return 0;}

int main() 
{
    EATEntry<decltype(CreateThread)> foo;
}