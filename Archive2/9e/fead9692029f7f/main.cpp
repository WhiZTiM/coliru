#include <iostream>

template <typename T>
class A;

template <typename T>
void fn(const A<T>& a);

template <typename T>
class A
{
    T d_priv;

    // Friend all types:
    //
    // template <typename U>
    // friend void fn(const A<U>&);
    
    // Friend this type:
    //
    // friend void fn<T>(const A<T>&);
    
    // Friend a specific type:
    //
    friend void fn<int>(const A<int>&);
    
  public:
    A(T t) : d_priv(t) {}
};

template <typename T>
void fn(const A<T>& a)
{
    std::cout << a.d_priv << std::endl;
}

int main()
{
    A<int>    a1(1);
    A<double> a2(1);

    fn(a1);
    fn(a2);
}