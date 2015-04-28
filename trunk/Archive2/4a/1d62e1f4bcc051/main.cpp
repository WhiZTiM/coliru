#include <iostream>
 
enum color
{
  red = 0,
  green,
  blue
};

#define COLOR_A green
//#define COLOR_B green //undefined

int main()
{
 
#ifdef COLOR_A
    std::cout << "1: COLOR_A=" << COLOR_A << ", OK\n";
#else
    std::cout << "1: no\n";
#endif

#if (COLOR_B == blue)
    std::cout << "2: COLOR_B is blue, DOH!\n";
#else
    std::cout << "2: no, OK\n";
#endif
 
 #if (defined(COLOR_A) && COLOR_A == blue)
    std::cout << "3: COLOR_A is blue, DOH!\n";
#else
    std::cout << "3: no, OK\n";
#endif

}