#include <vector>
#include <set>
#include <type_traits>
#include <iostream>

template <template <typename...> class> struct tag {}; 

template <typename T, template <typename...> class Base = std::vector>
class A : public Base<T>
{
public:    
    void add()
    {
        return _add(tag<Base>{});
    }
    
private:
    void _add(tag<std::set>)
    {
        std::cout << "set\n";
    }
    
    void _add(tag<std::vector>)
    {
        std::cout << "vector\n";
    }
};

int main()
{
    A<int> a;
    A<int, std::set> b;
    
    a.add();
    b.add();
}
