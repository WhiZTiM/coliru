#include <iostream>
#include <vector>
 
int p = 1;
template <typename T>
void foo(const std::vector<T> &v)
{
 
    // std::vector<T>::const_iterator is a dependent name,
    typename std::vector<T>::const_iterator it = v.begin();
 
    // without 'typename', the following is parsed as multiplication 
    // of the type-dependent member variable 'const_iterator' 
    // and some variable 'p'. Since there is a global 'p' visible
    // at this point, this template definition compiles.
    std::vector<T>::const_iterator* p; 
 
    typedef typename std::vector<T>::const_iterator iter_t;
    iter_t * p2; // iter_t is a dependent name, but it's known to be a type name
}
 
template<typename T>
struct S {
    typedef int value_t; // member of current instantiation
    void f() {
        S<T>::value_t n{};  // S<T> is dependenent, but 'typename' not needed
        std::cout << n << '\n';
    }
};
 
int main()
{
    std::vector<int> v;
    foo(v); // template instantiation fails: there is no member variable
            // called 'const_iterator' in the type std::vector<int>
    S<int>().f();
}