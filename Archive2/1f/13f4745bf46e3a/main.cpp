#include <iostream>
#include <fstream>

int main ()
{
  endl ((*new std::ofstream ("out.txt")) << *(new std::string {'h', 'e', 'l', 'l', 'o'}));
  ::system ("cat out.txt");
}