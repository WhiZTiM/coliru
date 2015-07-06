#include <iostream>
#include <utility>
#include <type_traits>


struct core_base { };
template<typename ... TT> struct CoreA : core_base { };
template<typename ... TT> struct CoreB : core_base { };

struct DerivedCoreA : CoreA<DerivedCoreA>
{
    void FooA() const { std::cout << "exec FooA" << std::endl; }
};

struct DerivedCoreB : CoreB<DerivedCoreB>
{
    void FooB() const { std::cout << "exec FooB" << std::endl; }
};

struct CoreUtilTest
{
    template<typename coretype>
    void Foo(coretype const * const pct) const
    {
        depends_on_type(pct);
    }
    void depends_on_type(DerivedCoreA const * const pct) const { pct->FooA(); }
    void depends_on_type(DerivedCoreB const * const pct) const { pct->FooB(); }
};

int main()
{
    using namespace std;
    CoreUtilTest CUT;
    DerivedCoreA A;
    DerivedCoreB B;

    cout << "call Foo with DerivedCoreA" << endl;
    CUT.Foo(&A);
    cout << "call Foo with DerivedCoreB" << endl;
    CUT.Foo(&B);
}
