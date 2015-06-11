#include<string>
#include<memory>
#include<iostream>

class my{
    
    public:
    int virtual  fun()=0;
    my(int x):a(x){}
    int a;
    my()=default;
    virtual ~my() {}
};
class der: public my{
    public:
    int fun(){ return 2;}
    ~der(){}
    
};
int main()
{
    der d;
}
