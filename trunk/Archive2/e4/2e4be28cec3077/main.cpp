#include <iostream>
#include <string>
#include <vector>
#include <memory>

std::string StrResize(const std::string& str, const char c, size_t size)
{
    std::string res;
    if(size == 0)
        return res;
    
    res.push_back(c);
    if(size == 1)
        return res;
        
    res += str.substr(0, size-2);
    size_t curr = res.size();
    
    for(size_t i=curr; i<size; ++i)
        res.push_back(c);
    
    return res;
}

void Menu(const std::vector<std::string>& options)
{
    size_t sz = 0;
    for(size_t i=0; i<options.size(); ++i)
        sz = std::max(sz, options[i].size());
    
    if(sz<2)
        sz = 2;
    
    std::cout << StrResize("", '*', sz+4) << std::endl;
    for(size_t i=0; i<options.size(); ++i)
        std::cout << StrResize(StrResize(options[i], ' ', sz+2) , '*', sz+4) << std::endl;
    std::cout << StrResize("", '*', sz+4) << std::endl;
}

int main()
{
    std::vector<std::string> op = {"1. prueba", "2. otra cosa", "3. otra opcion", "4. asfasdkljgadsjk sdag lkasdlkj gjlkas jlkas jklg"};
    Menu(op);
}
