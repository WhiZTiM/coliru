#include <iostream>
#include <string>
#include <sstream>
 
int main()
{
    std::string str = "Hello, world";
    std::istringstream in(str);
    std::string word1, word2;
 
    in >> word1;
    in.seekg(-5,in.end); // rewind
    in >> word2;
 
    std::cout << "word1 = " << word1 << '\n'
              << "word2 = " << word2 << '\n';
}