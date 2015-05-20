#include <iostream>
#include <vector>
#include <utility>

namespace A
{
    template<typename T> struct vector
    {
        // this will prevent the below B
        friend bool operator<( const vector&, const vector& ) { return true; };
    };
    // this allows the below B
    //template<typename T> bool operator<( const vector<T>&, const vector<T>& ) { return true; }
}

namespace B
{
    template<typename T> struct my_ref
    {
        T t;
        operator const T&() const { return t; } // let's say I need this for some reason...
    };
    // and I want only my_ref<my_ref and my_ref<U, but not U<my_ref:
    template<typename T> bool operator<(const my_ref<T>&,const my_ref<T>&) { return true; }
    template<typename T,typename U> bool operator<(const my_ref<T>&,const U&) { return true; }
    
    // oh, wait... we now have this:
    template<typename T,typename U> bool operator<(const T&,const my_ref<U>&) = delete;
}

int main()
{
    A::vector<int> v1, v2;
    B::my_ref<A::vector<int>> r1, r2;
    v1 < v2;
    r1 < v2;
    v1 < r2; // I don't want this to compile
    r1 < r2;
}
