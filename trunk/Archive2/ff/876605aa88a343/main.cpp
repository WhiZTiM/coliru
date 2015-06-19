#include <iostream>
#include <string>
#include <typeinfo>
 
template<typename FN>
inline void foo(FN&& fn) {
    std::cout << "before\n";
    fn();
    std::cout << "after\n";
}


template<typename FN>
inline void bar(FN fn) {
    std::cout << "before\n";
    fn();
    std::cout << "after\n";
}


void dostuff() {
    std::cout << "foo() inside\n";
}
 

int main(int argc, char* argv[]) {
    std::cout << "foo\n";
    foo([](){std::cout << "lambda inside\n";});
    foo(dostuff);
    
    std::cout << "\nbar\n";
    bar([](){std::cout << "lambda inside\n";});
    bar(dostuff);
    return 0;
}