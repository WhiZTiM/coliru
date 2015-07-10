//Demo Cpp-14 
#include<iostream>
using namespace std;

class F
{
    F(){}
    public:
    //F()=delete; //delete default ctor
    static F create() //nothing to do with any obj of the class
    {
        F b1;
    }
};

int main()
{
    F f1;
    return 0;
}