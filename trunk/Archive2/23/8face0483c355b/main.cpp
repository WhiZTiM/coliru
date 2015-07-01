#include <iostream>
#include <string>

#include <memory>
#include <cmath>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>

struct Opt {
public:
    Opt(const float& val) : val(val)
    {
        std::cout << "Opt ctor\n";
    }        
    
    float val;
};    

struct Guard {
    Guard() { std::cout << "start" << std::endl; }
    ~Guard() { std::cout << "end" << std::endl; }
};

Opt foo() {
    Guard lock;
    return 5;
}    

int main()
{
    std::cout << "result:" << foo().val << "\n";
    
    return 0;
}
