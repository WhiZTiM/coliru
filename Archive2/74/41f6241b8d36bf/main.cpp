#include <iostream>
using namespace std;

struct Interface
{
    virtual ~Interface() {}
    virtual void Foo() const = 0;
    virtual void Bar() const = 0;
    virtual void FooBar() const = 0;
};

struct ConcreteImplementation1 : public Interface
{
    void Foo() const {cout << __PRETTY_FUNCTION__ << endl;}
    void Bar() const {cout << __PRETTY_FUNCTION__ << endl;}
    void FooBar() const {Foo(); Bar();}
};

struct ConcreteImplementation2 : public Interface
{
    void Foo() const {cout << __PRETTY_FUNCTION__ << endl;}
    void Bar() const {cout << __PRETTY_FUNCTION__ << endl;}
    void FooBar() const {Foo(); Bar();}
    void BarFoo() const {Bar(); Foo();}
};

template<typename ToDecorate>
struct Decorator : virtual Interface, virtual ToDecorate
{
    Decorator(Interface const& i)
    : _i{i}
    {
    }
    
    void Foo() const {_i.Foo();}
    void Bar() const {_i.Bar();}
    void FooBar() const {cout << __PRETTY_FUNCTION__ << endl;}
    
    Interface const& _i;
};


int main() {
    ConcreteImplementation2 ci2;
    Decorator<ConcreteImplementation2> d(ci2);
    /*d.Foo();
    d.Bar();
    d.FooBar();*/
    ci2.Foo();
	
    //dynamic_cast<ConcreteImplementation2&>(d);
    
	return 0;
}