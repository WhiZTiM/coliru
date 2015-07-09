#include <iostream>
#include <cstdint>
#define bool int16_t /// ugly hack here
bool foo()
{
     int32_t i = -1;
     return i;
 
}
int main() {

    std::cout << foo();
}
