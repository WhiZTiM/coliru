    #include <iostream>
    
    struct N { enum { i = 1 }; };
    
    int main()
    {
        int N = 3;
        std::cout << N::i << '\n'; // prints 1
        std::cout << N << '\n'; // prints 3
    
        struct N { enum { i = 0 }; };
    
        std::cout << N::i << '\n'; // prints 0
    }
