#include <utility>
#include <iostream>

template <typename...>struct voider{using type=void;};
template <typename...A>using void_t = typename voider<A...>::type;

struct Struct1{};

#ifdef DEFINE_VISIT
template<class Visitor>
void visit(Visitor v,Struct1 s)
{
}
#endif

template <class Visitor>
using visit_t = decltype(visit(std::declval<Visitor>(), std::declval<Struct1>()));

template <typename Visitor, typename=void>
struct foo
{
    void operator()(){std::cout << "does not exist";}   
};

template <typename Visitor>
struct foo<Visitor,void_t<visit_t<Visitor>>>
{
    void operator()(){std::cout << "does exist";}   
};

int main()
{
    foo<int> a;
    a();
}