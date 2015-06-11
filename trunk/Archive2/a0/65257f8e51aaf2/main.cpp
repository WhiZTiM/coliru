#include <iostream>
#include <string>

static std::string const str("abc");
static char const cstr[] = "abcdefghij";


int main() { 
    std::cout << "size of " << str  << " = " << sizeof(str)  << std::endl;
    std::cout << "size of " << cstr << " = " << sizeof(cstr) << std::endl;  
}