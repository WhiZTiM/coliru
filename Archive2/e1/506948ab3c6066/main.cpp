#include <iostream>
#include <vector>

template<typename Container>
void foo(Container && v)
{
    v[100] = 1;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


int main()
{
    foo(std::vector<int>(1000));
    
    std::vector<int> buffer(100);
    foo(buffer);
}