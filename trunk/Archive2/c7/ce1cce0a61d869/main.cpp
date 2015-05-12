#include <iostream>
#include <memory>

struct Foo{
    Foo() :
    a_{0}, b_{1}, c_{-1}, combination_{0.5} {}
    
    int
        a_,
        b_,
        c_;
    double
        combination_;
};

int main()
{
    //int
    //    *unManagedArray = new int[16];
    std::unique_ptr<int[]>
        uniqueArrayOrigin = std::make_unique<int[]>(16);
    std::shared_ptr<int>
    //    sharedSingleTest{unManagedArray, std::default_delete<int[]>{}}, // works but needs call to new
        sharedSingleUnique = std::make_unique<int[]>(16)        // works, does not require call to new
    //  sharedSingleDerived = uniqueArrayOrigin                 // compilation error (conversion to non-scalar type)
    ;
    //  std::shared_ptr<int[]>
    //      sharedArrayTest{unManagedArray, std::default_delete<int[]>{}} // compilation errors
    //      sharedArrayUnique = std::make_unique<int[]>(16)     // compilation error (conversion to non-scalar type)
    //      sharedArrayDerived = uniqueArrayOrigin              // compilation error (conversion to non-scalar type)
    //;
    std::shared_ptr<Foo>
        nonArrayTest = std::make_unique<Foo>(); // works: specified overload of operator= for shared_ptr
        
    std::cout << "done!\n";
}
