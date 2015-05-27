// ConsoleApplication6.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <type_traits>

template <typename T, typename U>
void is_same_type(T, U)
{
    using DECAY_T = typename std::decay<T>::type;
    using DECAY_U = typename std::decay<U>::type;
    bool ret = std::is_same<DECAY_T, DECAY_U>::value;
    std::cout << "is_same? " << (ret?"yes":"no") << std::endl;
}

int f(int i)
{
    return i;
}

int main()
{
    if (auto ec1 = f(11) != 0) {
        is_same_type(ec1, 11);          
        is_same_type(ec1, true);        
    }
    
    if (auto ec1 = f(11)) {
        is_same_type(ec1, 11);
        is_same_type(ec1, true);
    }
    
    return 0;
}