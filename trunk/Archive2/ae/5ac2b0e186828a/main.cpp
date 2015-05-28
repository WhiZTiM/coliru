#include <iostream>
#include <string>
#include <vector>
#include <functional>



template <typename TMessage>
class Subscription {
public:
    virtual bool handle(const TMessage &) = 0;
};


template <typename TMessage, typename FnRet>
class Invoker {
public:
    Invoker(std::function<bool(const TMessage&)> f) :
		fn(f) {}
		
    virtual bool handle(const TMessage &message) {
        return fn(message);
    }
protected:
    std::function<bool(const TMessage&)> fn;
	
};


template <typename TMessage>
class Invoker<TMessage, void> {
public:
	Invoker(std::function<void(const TMessage&)> f) :
		fn(f) {}
		
    virtual bool handle(const TMessage &message) {
    	fn(message);
        return true;
    }
protected:
    std::function<void(const TMessage&)> fn;
};

class ClassA {
    public:
    bool boolFn(const char&) {
    	std::cout << "called ClassA::boolFn()" << std::endl;
        return false;   
    }
};

class ClassB {
    public:
    void voidFn(const float&) {  
    	std::cout << "called ClassB::voidFn()" << std::endl;
    }
};

int main()
{
    ClassA objA;
    ClassB objB;
    std::function<bool(const char&)> boolFn = std::bind(&ClassA::boolFn, &objA, std::placeholders::_1);
    std::function<void(const float&)> voidFn = std::bind(&ClassB::voidFn, &objB, std::placeholders::_1);
    
    Invoker<char, bool> normalCase(boolFn);
    char tmesg = 'A';
    normalCase.handle(tmesg);
    Invoker<char, void> voidCase(voidFn);
    voidCase.handle(tmesg);
}
