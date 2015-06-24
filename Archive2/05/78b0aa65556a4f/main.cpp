    #include <iostream>
    
    template<class C, class F>
    auto test(C c, F f) -> decltype((void)(c.*f)(), void())
        { std::cout << "member function\n"; }
    
    template<class C>
    void test(C c, int)
        { std::cout << "int\n"; }

    struct X {
        int f() { return 42; }
        double g(int) { return 3.14; }
    };
    
    int main()
    {
        X x;
        test(x, &X::f);  // ok - outputs "member function\n"
        // test(x, &X::g);  // CT error - f needs an argument
        test(x, 99);   // ok - outputs "int\n"
    }