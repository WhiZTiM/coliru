#include <memory>
#include <iostream>
 
struct Bad
{
    std::shared_ptr<Bad> getptr() {
        return std::shared_ptr<Bad>(this);
    }
    ~Bad() { std::cout << "Bad::~Bad() called\n"; }
};
 
int main()
{
    auto p = new Bad;
    auto sp = std::shared_ptr<Bad>(p);
    auto sp2 = std::shared_ptr<Bad>(p);
}