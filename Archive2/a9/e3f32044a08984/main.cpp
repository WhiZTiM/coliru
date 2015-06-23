#include <iostream>
#include <string>
struct Empty {};
struct Bit {unsigned bit:1; };
int main()
{
    Empty e;
    Bit b;
    std::string s1;
    std::string s2("askjfaksjdflkajsdlkfjalskdjflkjasldjflkasjdlfkjaskldjflskjdlf");
    std::cout << "size of empty string: "     << sizeof s1        << '\n'
              << "size of non-empty string: "     << sizeof s2        << '\n'
              << "size of pointer : "        << sizeof &e       << '\n'
              << "size of array of 10 int: " << sizeof(int[10]) << '\n';
}