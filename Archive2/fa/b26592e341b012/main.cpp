#include <iostream>
#include <string>
#include <stdint.h>

class Experience
{
    public:
    std::int64_t value;
    
    explicit Experience(std::int64_t value) : value(value) {}
    Experience(const Experience& rhs) : value(rhs.value) {}
    
    Experience& operator+=(const Experience& rhs)
    {
        value += rhs.value;
        return *this;
    }
    
    friend Experience operator+(Experience lhs, const Experience& rhs) {
        return lhs += rhs;
    }
    
    Experience& operator-=(const Experience& rhs)
    {
        value -= rhs.value;
        return *this;
    }
    
    friend Experience operator-(Experience lhs, const Experience& rhs) {
        return lhs -= rhs;
    }
};

int main()
{
    Experience xp(3);
    xp = Experience(2) + xp;
    std::cout << xp.value << std::endl;
}