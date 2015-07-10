    #include <iostream>
    
    struct Base { virtual void foo() = 0; };

    struct Derived : public Base
    {
        void foo() override { std::cout << "Derived\n"; }
    };

    struct FurtherDerived : public Derived
    {
        void foo() override { std::cout << "FurtherDerived\n"; }
    };
    
    int main()
    {
        Base* pbase = new FurtherDerived();
        pbase->foo(); // Can't inline this and have to go through vtable
        if (Derived* pderived = dynamic_cast<Derived *>(pbase))
        {
            pderived->foo();  // still dispatched to FurtherDerived
            pderived->Derived::foo();  // static dispatch to Derived
        }
    }