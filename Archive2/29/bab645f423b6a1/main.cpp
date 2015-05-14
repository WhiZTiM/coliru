#include <iostream>

template<class T> 
T deduce(T t) {
    return t;
} 

class Foo {
    struct Bar{ 
        int i; 
        Bar(int a = 5):i(a){}; 
    };
public:

  Bar *getB() { return new Bar(5); } // Leaks, doesn't matter for clarity's sake
};

int main() {
    Foo f;
    std::cout <<"b.i="<< deduce(f.getB())->i <<std::endl;
    return 0;
}