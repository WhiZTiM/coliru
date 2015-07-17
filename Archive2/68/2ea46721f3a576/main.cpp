#include <iostream>
#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>

class A{
    public:
    A(){std::cout<<"A says hi"<<std::endl;}
    ~A(){std::cout<<"A says bye"<<std::endl;}
};

int main()
{
    boost::scoped_ptr<A> p(new A());
    p.reset(NULL);
}
