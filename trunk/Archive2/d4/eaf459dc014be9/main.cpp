#include <iostream>

template<class ClassType, class rType, rType ClassType::*T> struct Holder{
    ClassType * ct;
    rType get(){ return ct->*T; }
    Holder(ClassType * t){ct=t;}
};

struct MyData{
    int myInt;
    Holder<MyData, int, &MyData::myInt> a=this;
};


int main(){
    MyData d;
    d.myInt=20;
    std::cout<<d.a.get()<<std::endl;

}
