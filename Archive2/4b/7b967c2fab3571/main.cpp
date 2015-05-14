
#include <iostream>
#include <string>
#include <type_traits>

struct A {
    A() = default;
	A(const A& other) { };
};

template<typename T>
std::enable_if_t<std::is_trivially_copyable<T>::value, void> f(const T&, const char* b) { std::cout << "b is std::string!" << std::endl; }

template<typename T>
void f(const T&, const std::string& b) { std::cout << "VS IS KILL!" << std::endl; }

int main() {
	std::cout << std::boolalpha << std::is_trivially_copyable<A>::value << std::endl;
	f(A(), "dicktits");
	f(A(), "dicktits");

}