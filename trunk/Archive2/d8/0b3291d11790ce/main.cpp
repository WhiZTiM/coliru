#include <iostream>
#include <set>

class A
{
public:
    A(int n): _n(n) {}

    int _n;
};

int main()
{
    std::set<A> coll;
    
    A a(1);
    coll.insert(a);
    
    std::set<A>::iterator b = coll.begin();
    std::cout << *b._n << std::endl;
}