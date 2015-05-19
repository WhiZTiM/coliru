#include <vector>
#include <chrono>
#include <iostream>

struct Timer {
    

struct GregorianDay {
    unsigned day = -1;
    
    GregorianDay(GregorianDay const& x)
    {
        set(x.day);
    }
    
    explicit GregorianDay(unsigned x)
    {
        set(x);
    }
    
    void set(int x){
        if(x < 1){ throw std::runtime_error("Day < 1"); }
        if(x > 31){ throw std::runtime_error("Day > 31"); }
        
        day = x;
    }
};

int main(){
    std::vector<GregorianDay> days;
    
    unsigned days_to_create = 1'000'000;
    
    std::cout << "GregorianDay size in bytes: " << sizeof(GregorianDay) << std::endl;
    std::cout << "Creating " << days_to_create << " days" << std::endl;
    for(unsigned i = 0; i < days_to_create; ++i){
        days.push_back(GregorianDay{1 + (i % 31)});
    }
}