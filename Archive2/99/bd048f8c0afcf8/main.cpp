#include <type_traits>
#include <iostream>
 
struct S {
    int operator()(int) { return 1; }
};

int normal(int) { return 1;}


int main()
{ 
    using t1 = std::result_of<S(int)>;
    using N = decltype((normal));    
    using t2 = std::result_of<N(int)>;
}