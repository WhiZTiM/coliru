#include <sstream>
#include <iostream>
#include <string>

int main()
{
    std::stringstream fake_cin("two words");
    
    char nextChar;
    std::string nextTerm;
    
    fake_cin.get(nextChar);              
    while (fake_cin && nextChar != ' ')
    {             
        nextTerm.push_back(nextChar);             
        fake_cin.get(nextChar); 
    }
    
    std::cout << nextTerm << '\n';
}