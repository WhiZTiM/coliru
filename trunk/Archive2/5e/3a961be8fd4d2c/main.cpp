#include <iostream>

class Abstract
{
public:
    Abstract(){ std::cout<<"1"<<std::endl;};
    Abstract( const Abstract& other ): mA(other.mA){ std::cout<<"2"<<std::endl;};
    virtual ~Abstract(){};

    void setA(double inA){mA = inA;};
    double getA(){return mA;};

    virtual void isAbstract() = 0;
protected:
    double mA;
};

class Parent : public virtual Abstract
{
public:
    Parent(){};
    Parent( const Parent& other ) : Abstract(other){};
    virtual ~Parent(){};

};


class Child : public virtual Parent
{
public:
    Child(){};
    Child( const Child& other ): Abstract(other), Parent(other) {};
    virtual ~Child(){};

    void isAbstract(){};
};


int main()
{
    Child child1;
    child1.setA(5);

    Child childCopy(child1);
    std::cout << childCopy.getA() << std::endl;
    return 0;
}