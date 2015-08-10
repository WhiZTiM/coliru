#include <iostream>

template<class ClassType, class rType> struct Holder{
    rType ClassType::* const T;
    ClassType * ct;
    rType get(){ return ct->*T; }
    explicit Holder(rType ClassType::*T, ClassType *t) : T(T), ct(t) {}
};

template<class ClassType, class rType> Holder<ClassType, rType> makeHolder(rType ClassType::*T, ClassType *t) {
    return Holder<ClassType, rType>(T, t);
}

struct MyData{
  int myInt;
};

int main(){
    MyData d;
    d.myInt=20;
    auto a = makeHolder(&MyData::myInt, &d);
    std::cout << a.get() << std::endl;

}
