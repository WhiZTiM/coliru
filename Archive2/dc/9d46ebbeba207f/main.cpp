#include <iostream>
#include <memory> 

class Helper {
public:
    Helper()      {std::cout << "Helper::Helper\n";};
    ~Helper()     { std::cout << "Helper::~Helper\n"; }
}; 
 
class Service
{
public:
    Service() { std::cout << "Service::Service\n";
    m_helper = std::unique_ptr<Helper>(new Helper()); }
    ~Service()     { std::cout << "Service::~Service\n"; }
    std::unique_ptr<Helper> m_helper;
    
};

 
int main()
{
    Service* s = new Service();
    printf("%p", (void*) s);
    delete s;
}