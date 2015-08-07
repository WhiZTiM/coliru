#include <sstream>
#include <iomanip>
#include <iostream> // cout

template <typename T>
std::string to_string(T value)
{
    std::ostringstream ostream;
    ostream << value ;
    return ostream.str() ;
}

int stoi(const std::string &str, std::size_t *pos=0, int base=10)
{
    std::istringstream istream(str);
    int value;
    istream >> std::setbase(base) >> value;
    if (pos)
        *pos = istream.tellg();
    return value;
}

float stof(const std::string &str, std::size_t *pos=0)
{
    std::istringstream istream(str);
    float value;
    istream >> value;
    if (pos)
        *pos = istream.tellg();
    return value;
}

int main()
{
    std::size_t pos;
    std::cout << to_string(3) << std::endl;
    
    std::cout << stoi("3") << std::endl;
    std::cout << stoi("99 bottles", &pos) << std::endl;
    std::cout << "read until " << pos << std::endl;
    std::cout << stoi("0xFF", 0, 16) << std::endl;
    
    std::cout << stof("3.14159265359") << std::endl;
    std::cout << stof("3.14159265359 radians equals 180 degrees", &pos) << std::endl;
    std::cout << "read until " << pos << std::endl;
}
