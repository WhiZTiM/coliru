#include <iostream>
#include <string>
#include <functional>

int dupa(int a, int b, int c)
{
    return a+b+c;
}

class Object{
    public:
    int dupa2(int a, int b, int c)
    {
        return a*b*c;
    }
};

int main(int argc, char* argv[])
{ 
    std::string str("World");
    std::function<int(int,int,int)> f = std::bind(&dupa, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    std::cout<<f(2,2,2)<<std::endl;
    
    Object obj;
    f = std::bind(&Object::dupa2,&obj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    std::cout<<f(2,2,2)<<std::endl;
}
