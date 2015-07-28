#include <iostream>
 
struct V {
    virtual void f() {};  // must be polymorphic to use runtime-checked dynamic_cast
};
struct A : virtual V {};
struct B : virtual V {
  B(V* v, A* a) {
    // casts during construction (see the call in the constructor of D below)
    dynamic_cast<B*>(v); // well-defined: v of type V*, V base of B, results in B*
    dynamic_cast<B*>(a); // undefined behavior: a has type A*, A not a base of B
  }
};
struct D : A, B {
    D() : B((A*)this, this) { }
};
 
struct Base {
    virtual ~Base() {}
};
 
struct Derived: Base {
    virtual void name() {}
};
 
int main()
{
    D d; // the most derived object
    A& a = d; // upcast, dynamic_cast may be used, but unnecessary
    //V* v1 = new D;
    A* a1 = new D;
    //D* new_d = new D;
    //new_d = dynamic_cast<D&>(a); // downcast
    if(D* new_d = dynamic_cast<D*>(a1))
    {
        std::cout << "downcast from a to d successful\n";
    }
    
    //B* new_b = new B;
    //new_b = dynamic_cast<B&>(a); // sidecast
    if(B* new_b = dynamic_cast<B*>(a1))
    {
        std::cout << "sidecast from a to b successful\n";
    }
 
 
    Base* b1 = new Base;
    if(Derived* d = dynamic_cast<Derived*>(b1))
    {
        std::cout << "downcast from b1 to d successful\n";
        d->name(); // safe to call
    }
 
    Base* b2 = new Derived;
    if(Derived* d = dynamic_cast<Derived*>(b2))
    {
        std::cout << "downcast from b2 to d successful\n";
        d->name(); // safe to call
    }
 
    delete b1;
    delete b2;
}