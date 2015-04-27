#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <memory>


class TestClass
{
    public:
    TestClass(std::string a):name(a)
    {
        std::cout << name << " is created" << std::endl;
    }
    
    void print()
    {
        std::cout << "i am " << name  << std::endl;
    }
    
    ~TestClass()
    {
        std::cout << name << " is dead" << std::endl;
    }
    
    std::string name;
};

void fillVector(std::vector<std::unique_ptr<TestClass> >& vec)
{
    TestClass* a(new TestClass("A"));    
    std::unique_ptr<TestClass> b(new TestClass("B"));
    
    vec.push_back(std::unique_ptr<TestClass>(a));
    vec.push_back(std::move(b));
}

void fun(std::unique_ptr<TestClass> temp)
{
    temp->print();
}

int main()
{
    std::vector<std::unique_ptr<TestClass> > aVec;
    
    fillVector(aVec);
    
    for (auto it = aVec.begin(); it != aVec.end() ; it++)
    {
        fun(el);
    }
    
    std::cout << "hello" << std::endl;
    if (aVec.empty())
    {
        std::cout << "is empty" << std::endl;
    }
}
