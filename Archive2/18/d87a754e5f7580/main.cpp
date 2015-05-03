#include <iostream>

template <typename T> 
struct S{
    template <typename U> void func(){
        std::cout << "In S::func\n";
    }
};

// In order to make member template function is visible in function test,
// defining a global template function **func** whose name is same with one 
// member template function in struct S.
template <typename M>
void func(){
    std::cout << "from ordinary func\n";
}

template <typename M>
void test(){
    S<M> s;
    func<M>();     // test func template function is visible in test function
    s.func<M>();     
}
int main(){    
    test<int>();
}
