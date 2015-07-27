#include <iostream>
 
int main()
{
#ifdef __unix
    std::cout << "unix\n";
#endif

#ifdef _WIN32
    std::cout << "windows\n";
#endif
}