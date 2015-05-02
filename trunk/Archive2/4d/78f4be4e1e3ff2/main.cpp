#include <iostream>
struct Empty {};
struct Bit {unsigned bit:1; };
int main()
{
    
    int i = 100;
    nValue = static_cast<int>(i / 2.5);
    
    std::cout << nValue <<std::endl;
    
    Empty e;
    Bit b;
    std::cout << "size of empty class: "     << sizeof e        << '\n'
              << "size of pointer : "        << sizeof &e       << '\n'
//            << "size of function: "        << sizeof(void())  << '\n'  // compile error
//            << "size of incomplete type: " << sizeof(int[])   << '\n'  // compile error
//            << "size of bit field: "       << sizeof b.bit    << '\n'  // compile error
              << "size of array of 10 int: " << sizeof(int[10]) << '\n';
}