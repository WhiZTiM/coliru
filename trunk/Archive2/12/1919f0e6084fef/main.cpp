#include <iostream>
#include <memory>
class A {
public:
//    A(const A&) { std::cout << "copy A" << '\n'; }
    A(A&&) { std::cout << "move A" << '\n'; }
    A(std::unique_ptr<int>&& u_ptr) : u_ptr(std::move(u_ptr)) {}
    const int& getInt() { return *u_ptr; }

private:
    std::unique_ptr<int> u_ptr;
};

class B {
public:
    B(int u_ptr) : u_ptr(new int(u_ptr)) {}
    A toA() && { return A(std::move(u_ptr)); }
 
private:
    std::unique_ptr<int> u_ptr;
};

int main() {
    B b(-1);
    A a(std::move(b).toA());
    std::cout << a.getInt() << '\n';
    return 0;
}
