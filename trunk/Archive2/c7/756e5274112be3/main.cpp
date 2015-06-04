#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;

class Base
{
    public:
        Base () {cout << "Base ctor" << endl;}
        virtual ~Base () { cout << "Base dtor" << endl;}
        virtual void foo () {cout << "Base Foo!" << endl;}
};

class Derived : public Base
{
    public:
        Derived () {cout << "derived ctor" << endl;}
        ~Derived () {cout << "derived dtor" << endl;}
    
    void foo () {cout << "Derived Foo!" << endl;}
    
    void bar () {cout << "Derived bar!" << endl;}
};

int main()
{
    std::shared_ptr<Base> spBase (new Derived ());
    spBase->foo ();
 
    // Cast a shared_ptr to base a shared_ptr to derived:
    {
        std::shared_ptr<Derived> spDerived = std::static_pointer_cast<Derived> (spBase);
        spDerived->bar ();
    }
    
    // Cast a shared_ptr to base a raw ptr to derived (have to retain original shared ptr)
    {
        static_cast<Derived*> (spBase.get ())->bar ();
    }
    
    // Making a new shared ptr to derived from the content of the shared ptr to base will compile,
    // but will crash (because you now have two unrelated shared_ptrs managing and deleting the same reference)
    {
        //std::shared_ptr<Derived> spDerived (static_cast<Derived*> (spBase.get ()));
        //spDerived->foo ();
    }
    
 }