    #include <iostream>
    
    struct N { enum { i = 1 }; };
    
    int main()
    {
        int N;
        std::cout << N::i << '\n'; // prints 1
    
        struct N { enum { i = 0 }; };
    
        std::cout << N::i << '\n'; // prints 0
    }
