#include <vector>
#include <iostream>

template< class T>
struct has_iterator
{
    private:
    
    template<class U, long A = sizeof(typename U::const_iterator)>
    static std::integral_constant<bool, true> try_assign(U&&);
    static std::integral_constant<bool, false> try_assign(...);
    
    public:
    typedef decltype(try_assign(std::declval<T>())) type;
};

struct A
{
    typedef int const_iterator;
};

int main()
{
    std::cout << has_iterator<std::vector<int> >::type::value << std::endl;
    std::cout << has_iterator<int >::type::value << std::endl;
    std::cout << has_iterator<A >::type::value << std::endl;
}