#include <iostream>
#include <string>

struct Lifetime {
    std::string name;
    
    Lifetime(std::string n)
    : name(n) 
    {
        std::cout << name << " lives!" << std::endl;
    }
    
    ~Lifetime(){
        std::cout << name << " dies" << std::endl;
    }
};

int main() {
    Lifetime kane("kane");
    {
        Lifetime mario("Mario");
    }
    Lifetime isaac("Isaac");
    Lifetime("Sir Kort");
}