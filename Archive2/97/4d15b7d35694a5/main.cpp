#include <iostream>
#include <string>
#include <vector>
#include <memory>

static const char space = ' ';

std::string MakeLine(const char left, const std::string& str, const char c, size_t size, const char right)
{
    std::string res;
    res.push_back( left );
    res.push_back( space );
    res += str.substr( 0, size );
    if( size > str.size() ) 
        res += std::string( size - str.size(), c );
    res.push_back( space );
    res.push_back( right );
    return res;
}

void Menu(const std::vector<std::string>& options)
{
    size_t sz = 0;
    for(size_t i=0; i<options.size(); ++i)
        sz = std::max(sz, options[i].size());
    
    if(sz<2)
        sz = 2;
    
    std::cout << MakeLine('/', "", '-', sz, '\\') << std::endl;
    for(size_t i=0; i<options.size(); ++i)
        std::cout << MakeLine('|',options[i], space, sz, '|') << std::endl;
    std::cout << MakeLine('\\', "", '-', sz, '/') << std::endl;
}

int main()
{
    std::vector<std::string> op = {"1. prueba", "2. otra cosa", "3. otra opcion", "4. asfasdkljgadsjk sdag lkasdlkj gjlkas jlkas jklg"};
    Menu(op);
}
