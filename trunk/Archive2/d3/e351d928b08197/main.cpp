#include <iostream>
struct Empty {
int a;
};
struct Bit {unsigned bit:1; };
int main()
{
    Empty e;
    Empty *e1;
    std::cout << "size of empty class: "     << sizeof e        << '\n'
              << "size of pointer: "        << sizeof &e       << '\n'
              << "size of pointer to e1: "     << sizeof e1       << '\n'
              << "size of \te1: \""     << sizeof *e1       << '\n'
//            << "size of function: "        << sizeof(void())  << '\n'  // compile error
//            << "size of incomplete type: " << sizeof(int[])   << '\n'  // compile error
//            << "size of bit field: "       << sizeof b.bit    << '\n'  // compile error
              << "size of array of 10 int: " << sizeof(int[10]) << '\n';
}