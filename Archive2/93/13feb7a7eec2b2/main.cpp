#include <iostream>
#include <map>

void foo (std::map<int,int>::key_type*) { std::cout << "a" << std::endl; }
void foo (std::map<int,int>*) { std::cout << "b" << std::endl; }

template <typename T>
void bar (typename T::key_type*) { std::cout << "a" << std::endl; }
template <typename T>
void bar (T) { std::cout << "b" << std::endl; }

int main ()
{
    // foo (nullptr); Error: ambiguous
    // auto x = &bar<std::map<int,int>>; // Error: ambiguous
    bar<std::map<int,int>> (nullptr); // prints "a"
}