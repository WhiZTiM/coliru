#include <iostream>
#include <memory>
 
void foo(const std::shared_ptr<std::string>& i)
{
    //(*i)++;
    i->append("bbb");
    std::cout<<i->c_str()<<std::endl;
}
 
int main()
{
    auto sp = std::make_shared<std::string>("aaa");
    std::cout<<sp->c_str()<<std::endl;
    foo(sp);
    //std::cout << *sp << std::endl;
    std::cout<<sp->c_str()<<std::endl;
}