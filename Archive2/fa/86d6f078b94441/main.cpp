#include <iostream>
#include <utility>
#include <type_traits>
#include <vector>

struct visitor;
struct CoreBase
{
    void accept(visitor const & v) const;
};
template<typename ... TT> struct ContainerTypeA : CoreBase { };
template<typename ... TT> struct ContainerTypeB : CoreBase { };
template<typename ... TT> struct ContainerTypeC : CoreBase { };

struct DerivedA : ContainerTypeA<DerivedA>
{
    void SpecificToA() const { std::cout << "called SpecificToA" << std::endl; }
};

struct DerivedB : ContainerTypeB<DerivedB>
{
    void SpecificToB() const { std::cout << "called SpecificToB" << std::endl; }
};

struct DerivedC : ContainerTypeC<DerivedC>
{
    void SpecificToC() const { std::cout << "called SpecificToC" << std::endl; }
};

namespace detail
{
    template <typename T>
    struct is_derived_from_generic
    {
        typedef std::integral_constant<int, 0> _0;
        typedef std::integral_constant<int, 1> _1;
        typedef std::integral_constant<int, 2> _2;
        typedef std::integral_constant<int, 3> _3;

        template <typename... Args>
        static _1 test(ContainerTypeA<Args...>*);
        template <typename... Args>
        static _2 test(ContainerTypeB<Args...>*);
        template <typename... Args>
        static _3 test(ContainerTypeC<Args...>*);

        static _0 test(void*);

        static constexpr int value = decltype(test(std::declval<T*>())) { };
    };
}

template <typename T>
struct is_derived_from_generic : std::integral_constant<int, detail::is_derived_from_generic<T>::value> { };

struct visitor
{
    template<typename T, int I = 0>
    void visit (T * const t) const { }
//    template<typename T>
//    void visit<T, 1> (T * const t) const { }

    void foo() const {}
};

void CoreBase::accept(visitor const & v) const { v.visit(this); }

int main()
{
    using namespace std;
    using pobj = shared_ptr<CoreBase>;
    
    vector<pobj> vec;
    
    vec.push_back(make_shared<DerivedA>());
    vec.push_back(make_shared<DerivedB>());
    vec.push_back(make_shared<DerivedC>());

    visitor vis;
    
    cout << is_derived_from_generic<DerivedA>::value << endl;
    cout << is_derived_from_generic<DerivedB>::value << endl;
    cout << is_derived_from_generic<DerivedC>::value << endl;

    for (pobj p : vec)
    {
        p->accept(vis);
    }

}

