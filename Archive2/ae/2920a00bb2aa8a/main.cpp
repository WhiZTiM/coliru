#include <iostream>
#include <utility>

class A {
    int& c;
    int d;
    
public:
    A(int& i, int j) : c(i), d(j) {}
    
    A& operator=(A&& other) {
        d = other.d;
        return *this;
    }
    
    int f()
    {
        return c + d;   
    }
};

int main() {
    int t = 5;
    A a(t, 4), b(t, 5);    
    b = std::move(a);
    std::cout << a.f() << std::endl;
}
