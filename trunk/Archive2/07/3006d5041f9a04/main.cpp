#include <sstream>
#include <iostream>
int main()
{
    std::stringstream s1("Hello, world"); // IO stream
    s1.get();
    if(s1.putback('Y')) // modifies the buffer
        std::cout << s1.rdbuf() << '\n';
    else
        std::cout << "putback failed\n";
 
    std::istringstream s2("Hello, world"); // input-only stream
    s2.get();
    if(s2.putback('Y')) // cannot modify input-only buffer
        std::cout << s2.rdbuf() << '\n';
    else
        std::cout << "putback failed\n";
 
    s2.clear();
    if(s2.putback('H')) // non-modifying putback
        std::cout << s2.rdbuf() << '\n';
    else
        std::cout << "putback failed\n";
}