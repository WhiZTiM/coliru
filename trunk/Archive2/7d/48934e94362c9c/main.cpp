#include <vector>
#include <set>
#include <utility>
#include <iostream>

template <template <typename...> class> struct tag {}; 

template <typename T, template <typename...> class Base = std::vector>
class A : public Base<T>
{
public:
    void add(const T& t)
    {
        return _add(tag<Base>{}, t);
    }
    
private:
    void _add(tag<std::set>, const T& t)
    {
        std::cout << "set\n";
        Base<T>::insert(t);
    }
    
    void _add(tag<std::vector>, const T& t)
    {
        std::cout << "vector\n";
        Base<T>::push_back(t);
    }
};

int main()
{
    A<int> a;
    A<int, std::set> b;
    
    a.add(1);
    b.add(1);
}
