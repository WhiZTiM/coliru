#include <list>
#include <iostream>
#include <iterator>
 
int main( )
{
int k = 0;
for (float i = 0.f; i < 10000.f; i+=0.00001f) {
 ++k;
}
std::cout << k << std::endl;
std::cout << "dsdsd" << std::endl;
}