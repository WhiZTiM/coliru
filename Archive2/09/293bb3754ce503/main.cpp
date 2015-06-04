#include <iostream>
#include <string>
#include <vector>
#include <memory>


class A
{
    public:
    A(std::string iName):name(iName)
    {}
    
    std::string print()
    {
        //std::cout << "return class " << otherClass->print() << std::endl;
        return name;
    }
    A* getNextClass()
    {
        //std::cout << "return class " << otherClass->print() << std::endl;
        return otherClass;
    }
    
    A* lastClassWithoutOtherClass()
    {
        if (otherClass)
        {
            A* someClass = otherClass;
            while (someClass->getNextClass())
            {
                someClass = someClass->getNextClass();
            }
            return someClass;
        }
        return this;
        
        /*
        if (otherClass)
        {
            return otherClass->lastClassWithoutOtherClass();
        }        
        return this;
        */
    }
    
    std::string name;
    A* otherClass;
};

int main()
{
    std::unique_ptr<A> classA(new A("A"));
    std::unique_ptr<A> classB(new A("B"));
    std::unique_ptr<A> classC(new A("C"));
    
    classB->otherClass = classC.get();
    classA->otherClass = classB.get();
    
    A* someClass = classA->lastClassWithoutOtherClass();
    
    std::cout << someClass->print();
}
