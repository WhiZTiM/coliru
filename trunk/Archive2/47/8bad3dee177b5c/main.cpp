#include <iostream>
 
enum color
{
  red = 0,
  green,
  blue
};

#define MY_COLOR green

int main()
{
 
#ifdef MY_COLOR
    std::cout << "1: MY_COLOR=" << MY_COLOR << "\n";
#else
    std::cout << "1: no\n";
#endif

#if (MY_COLOR == blue)
    std::cout << "2: MY_COLOR is blue\n";
#else
    std::cout << "2: no\n";
#endif
 
 #if (defined(MY_COLOR) && MY_COLOR == blue)
    std::cout << "3: MY_COLOR is blue\n";
#else
    std::cout << "3: no\n";
#endif

}