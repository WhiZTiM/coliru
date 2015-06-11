#include <vector>
#include <iostream>

struct T
{
    T() { std::cout << "!\n"; }
    T(const T&) { std::cout << "*\n"; }
    ~T() { std::cout << "~\n"; }
};

int main()
{
    std::vector<T>* ptr = new std::vector<T>();
    ptr->emplace_back();
    ptr->emplace_back();
    ptr->emplace_back();
    
    delete(ptr);  // expecting as many "~" as "!" and "*" combined
}
