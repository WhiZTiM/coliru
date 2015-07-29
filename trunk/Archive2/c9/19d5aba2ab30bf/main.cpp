#include <iostream>

class Helper {
public:
    Helper()      {std::cout << "Helper::Helper DO something very long and heavy. \n";};
    ~Helper()     { std::cout << "Helper::~Helper\n"; }
}; 

class Service
{
public:
    Service() { std::cout << "Service::Service\n";};
    ~Service()     { std::cout << "Service::~Service\n"; }
    Helper* m_helper;
    
};

 
int main()
{
    Service* s = new Service();
    printf("%p\n", (void*) s);
    delete s;
}


