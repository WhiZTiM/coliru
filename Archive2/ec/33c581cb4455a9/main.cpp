#include <iostream>

class A {
private:
    void foo() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    void foo(int) {std::cout << __PRETTY_FUNCTION__ << std::endl;}
    void foo(int, char) {std::cout << __PRETTY_FUNCTION__ << std::endl;}
    void foo(bool, int, double) {std::cout << __PRETTY_FUNCTION__ << std::endl;}
    void bar(int) {std::cout << __PRETTY_FUNCTION__ << std::endl;}
    void bar(bool, int, double) {std::cout << __PRETTY_FUNCTION__ << std::endl;}
public:
    template <typename... Args> 
    auto doIt_impl(int, Args&&... args) -> decltype(bar(std::forward<Args>(args)...)){
        bar(std::forward<Args>(args)...);
    }
    template <typename... Args> 
    auto doIt_impl(long, Args&&... args) -> void{
        foo(std::forward<Args>(args)...);
    }
    template <typename... Args> void execute(Args&&... args) {foo(std::forward<Args>(args)...);}
    template <typename... Args> void doIt(Args&&... args) {doIt_impl(0, std::forward<Args>(args)...);}
};

int main() {
    A a;
    a.doIt();
    a.doIt(1);
    a.doIt(5,'t');
}