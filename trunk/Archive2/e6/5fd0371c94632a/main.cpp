#include <iostream>
#include <type_traits>
#include<functional>

using namespace std;

template <typename T, typename = typename std::enable_if_t<std::is_same<T, int>::value>>
struct ImplementationA {
    void print() { std::cout << "A\n"; }    
};

template <typename T, typename = typename std::enable_if_t<std::is_same<T, double>::value>>
struct ImplementationB {
    void print() { std::cout << "B\n"; }
};

template <typename T, typename = void> class ProjectClass;

template <typename T>
struct ProjectClass<T, typename std::enable_if_t<std::is_same<T, int>::value>> 
    : ImplementationA<T>{};

template <typename T>
struct ProjectClass<T, typename std::enable_if_t<std::is_same<T, double>::value>> 
    : ImplementationB<T>{};

int main() {
    ProjectClass<double> x;
    ProjectClass<int> y;

    x.print(); // Prints "B"
    y.print(); // Prints "A"
    return 0;
}