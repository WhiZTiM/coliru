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
            // works but needs call to new
    //  sharedSingleTest{unManagedArray, std::default_delete<int[]>{}}; 
            // works, does not require call to new
        sharedSingleUnique = std::make_unique<int[]>(16);       
            // compilation error (conversion to non-scalar type)
    //  sharedSingleDerived = uniqueArrayOrigin;                
    
    //  std::shared_ptr<int[]>
                // compilation errors
    //      sharedArrayTest{unManagedArray, std::default_delete<int[]>{}};
                // compilation error (conversion to non-scalar type)
    //      sharedArrayUnique = std::make_unique<int[]>(16);
                // compilation error (conversion to non-scalar type)
    //      sharedArrayDerived = uniqueArrayOrigin;

    std::shared_ptr<Foo>
            // works: specified overload of operator= for shared_ptr
        nonArrayTest = std::make_unique<Foo>(); 
        
    std::cout << "done!\n";
}
