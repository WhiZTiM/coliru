#include <iostream>
#include <memory>
 
void foo(std::shared_ptr<int> i)
{
    (*i)++;
}
 
int main()
{
    auto sp = std::make_shared<int>(10);
    foo(sp);
    std::cout << *sp << std::endl;
}