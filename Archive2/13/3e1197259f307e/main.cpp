#include <iostream>
#include <vector>
#include <functional>

struct base
{
    virtual ~base() = default ;
    virtual void foo() const { std::cout << "base " ; }
    // ...
};

template < int TYPE_TAG > struct derived : base
{ virtual void foo() const override { std::cout << "derived#" << TYPE_TAG << ' ' ; } };

int main()
{
    base b ; derived<1> d1 ; derived<2> d2 ; derived<3> d3 ; derived<4> d4 ; derived<5> d5 ;

    // vector of wrapped references
    std::vector< std::reference_wrapper<base> > seq { b, d1, d2, d3  };
    seq.push_back(d4) ;
    seq.emplace_back(d5) ;

    struct yet_another_derived_class : base
    { virtual void foo() const override { std::cout << "yet_another_derived_class " ; } };
    yet_another_derived_class adc ;
    seq.emplace_back(adc) ;

    for( base& b : seq ) b.foo() ;
    std::cout << '\n' ;

    seq.pop_back() ; // adc will be destroyed before seq
    // ...
}
