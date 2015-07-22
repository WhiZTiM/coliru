#include <iostream>
#include <map>
#include <memory>

struct Proxy
{
    typedef std::map<int, int> InputDataMap;    
    int a;
};

template<class C, class D>
void InsertDataIntoInputMap(
    const typename C::InputDataMap::key_type& key,
    const D&& val)
{
    std::cout << "Not shared\n";
}

template<class C, class D>
void InsertDataIntoInputMap(
    const typename C::InputDataMap::key_type& key,
    const std::shared_ptr<D> val)
{
    if (val)
    {
        std::cout << "Shared\n";
    }
}

int main() {
    int a;
    std::shared_ptr<double> x(new double(4.5));

    InsertDataIntoInputMap<Proxy>(a, x);
}
