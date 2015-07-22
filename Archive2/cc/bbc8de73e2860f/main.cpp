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
    std::cout << "In base\n";
}

template<class C, class D>
void InsertDataIntoInputMap(
    const typename C::InputDataMap::key_type& key,
    const boost::shared_ptr<D> val)
{
    if (val)
    {
        std::cout << "In overload\n";
    }
}

int main() {
    int a;
    boost::shared_ptr<double> x(new double(4.5));
    const double y = 4.5;
    
    InsertDataIntoInputMap<Proxy>(a, x);
    InsertDataIntoInputMap<Proxy>(a, y);
}
/*


#include <iostream>
#include <memory>


template <bool PtrT>
struct TestPtr{};

template <>
struct TestPtr<true>
{
    template <class T>
    static void f(T* ptr)
    {
        std::cout << "Got a ptr" << std::endl;
    }
};

template <>
struct TestPtr<false>
{
    template <class T>
    static void f(T t)
    {
        std::cout << "Didn't get a ptr" << std::endl;
    }
};

template <class T, bool TIsPtr=std::is_pointer<T>::value>
void test(const T& t)
{
    TestPtr<TIsPtr>::f(t);
}


class A
{

};


int main()
{
    A* ptr;
    A a;

    test(a);
    test(ptr);


}



*/