#include <iostream>
#include <vector>
int main()
{
    std::vector<int> v;
    std::cout << "Default-constructd capacity is " << v.capacity() << '\n';
    v.resize(100);
    std::cout << "Capacity of a 100-element vector is " << v.capacity() << '\n';
    v.clear();
    std::cout << "Capacity after clear() is " << v.capacity() << '\n';
    v.shrink_to_fit();
   // std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';
}