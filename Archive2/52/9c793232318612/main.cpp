#include <iostream>

using std::swap;

namespace N{
    class A{
        
    };

    void foo(A& x){
        std::cout << "in N:foo\n";        
    }

    void swap(A &x, A& y){
         std::cout << "In N:swap\n";
    }        
}

// template <typename T>
void foo(N::A& x){
    std::cout << "In global scope" << std::endl;
}



int main(){
    N::A a, b;

    foo(a);
    swap(a, b);
    return 0;
}
