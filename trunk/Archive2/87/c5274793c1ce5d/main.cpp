#include <iostream>
#include <memory>

struct texture { /* ... */ virtual ~texture() { std::cout << "destrutor\n" ; } };

struct A
{
    A() = default ;

    // pass texture objects which do not have a dynamic storage duration by reference
    A( texture& t ) : ptr( std::addressof(t), []( texture*){} ) {} // do nothing deleter

    // pass texture objects with dynamic storage duration wrapped in a shared pointer
    template < typename TEXTURE_TYPE >
    A( const std::shared_ptr<TEXTURE_TYPE>& pt ) : ptr(pt) {}

    template < typename TEXTURE_TYPE >
    A( std::shared_ptr<TEXTURE_TYPE>&& pt ) : ptr( std::move(pt) ) {}

    std::shared_ptr<texture> ptr ;
};

int main()
{
    static texture x ; // texture#1
    A a1(x) ; // passed by reference 

    A a2( std::make_shared<texture>() ) ; // texture#2

    auto y = std::make_shared<texture>() ; // texture#3
    A a3(y) ;

    struct derived_texture : texture { ~derived_texture() { std::cout << "derived class "; } };

    derived_texture d1 ; // texture#4
    A a4(d1) ; // passed by reference. note: a4 is destroyed before d1

    A a5( std::make_shared<derived_texture>() ) ; // texture#5
}
