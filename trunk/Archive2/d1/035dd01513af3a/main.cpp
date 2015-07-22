#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>

struct Proxy
{
    typedef std::map<int, int> InputDataMap;    
    int a;
};

template<class C, class D>
void InsertDataIntoInputMap(
    const typename C::InputDataMap::key_type& key,
    const D val)
{
    std::cout << "Not shared\n";
}

template<class C, class D>
void InsertDataIntoInputMap(
    const typename C::InputDataMap::key_type& key,
    const boost::shared_ptr<D> val)
{
    if (val)
    {
        std::cout << "Shared\n";
    }
}

int main() {
    int a;
    boost::shared_ptr<double> x(new double(4.5));

    InsertDataIntoInputMap<Proxy>(a, x);
}