struct outer
{
    // C++11
    
    // way 0
    struct /* unnamed */
    {
        int x;
    } m;
    decltype(m) my_function()
    {
        return {42};
    }
    
    // way 1
    void dummy()
    {
        auto lambda = []{
            struct /* unnamed */
            {
                double d;
            } x{4.2};
            
            return x;
        };
        
        auto x = lambda();
        (void)x; // prevent warning: "x not used"
    }
    
    
    // C++14
    auto my_other_function()
    {
        struct /* unnamed */
        {
            double d;
        } x{4.2};
        
        return x;
    }
};

#include <iostream>

int main() { std::cout << "compiled successfully\n"; }