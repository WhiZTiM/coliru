#include <iostream>
#include <string>
#include <exception>

class MyException : public std::exception
{
    std::string desc ;
public:
    MyException(const std::string& str) : desc{str} {}
    
   const char* what() const noexcept { return desc.c_str(); }
};

int main()
{
    try {
        throw MyException("Error !!!");
    } catch (std::exception& e) {
        std::cout << e.what();
    }
}