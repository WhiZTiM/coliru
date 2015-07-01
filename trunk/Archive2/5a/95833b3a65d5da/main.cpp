#include <iostream>
#include <string>

#include <memory>
#include <cmath>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>

struct Guard {
    ~Guard() {
        std::cout << "~Guard()\n";
    }    
};    

struct Opt {
public:
    Opt(const float& val) : val(val)
    {
        std::cout << "Opt ctor\n";
    }        
    
    float val;
};    

Opt foo() {
    Guard guard;
    return 5;
}    

int main()
{
    std::cout << "result:" << foo().val << "\n";
    
    return 0;
}
