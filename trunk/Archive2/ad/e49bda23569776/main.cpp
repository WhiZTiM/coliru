#include <iostream>
#include <string>
int main()
{
    std::string s1 = "Test";
    std::string s2 = "Best";
//    std::string&& r1 = s1; // error: can't bind to lvalue
 
    const std::string& r2 = s1 + s2; // OK, lvalue ref to const extends lifetime
//    r2 += "Test"; // error: can't modify through reference to const
 
    std::string& r3 = s1  ; // OK, rvalue ref extends lifetime
    r3 += "Test"; // this object can be modified
    r3 += s2 + "wer";
    std::cout << r3 << '\n';
}