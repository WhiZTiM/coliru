#include <iostream>
#include <string>
#include <sstream>
#include <memory>

class MyClass {

    public:
		MyClass(std::string name);
		virtual ~MyClass();
        
    private: 
        std::string myName;
};

MyClass::MyClass(std::string name) : myName(name) {}
MyClass::~MyClass() {}

class OtherClass {
    
    public:
        OtherClass();
        virtual ~OtherClass();
        
        void MyFunction(std::string data);
        
        std::unique_ptr<MyClass> theClassPtr;
};

OtherClass::OtherClass() {}
OtherClass::~OtherClass() {}

void OtherClass::MyFunction(std::string data)
{
    auto test = std::make_unique<MyClass>(data);
    theClassPtr = std::move(test);
}

int main()
{
    OtherClass test;
    test.MyFunction("This is a test");
}
