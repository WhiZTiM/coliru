#include <iostream>
#include <string>

#include <memory>
#include <cmath>
#include <vector>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>

void foo(std::vector<int>&& v) {
}    

struct A {
    A(int a) : a(a) {}
    
    A(const A&) {
        std::cout << "A(A&)\n";
    }
    
    A(A&&) {
        std::cout << "A(A&&)\n";
    }
    
    int a = 5;
};    

void print(const std::vector<A>& v) {
    for (const auto& item : v) {
        std::cout << item.a << "\n";
    }        
}    

int main()
{
    std::vector<A> in = {1, 2, 3};
    std::vector<A> out;
    
    for (auto&& item : in) {
        out.push_back(std::move(item));
    }        
    
    std::cout << "in:\n";
    print(in);
    
    std::cout << "out:\n";
    print(out);

    return 0;
}
