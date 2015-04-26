#include <iostream>
#include <functional>
#include <string>
#include <map>

struct function_map
{
    using function_type = std::function< void() > ;

    template < typename FN, typename... ARGS >

    bool insert( std::string key, FN&& fn, ARGS&&... args )
    { return function_map.emplace( std::move(key), std::bind( std::forward<FN>(fn), std::forward<ARGS>(args)... ) ).second ; }

    bool call( const std::string& key )
    {
        const auto iter = function_map.find(key) ;
        if( iter != function_map.end()  ) { iter->second() ; return true ; }
        else return false ;
    }

    private: std::map< std::string, function_type > function_map ;
};

double non_member_fun( int a, double b, short c )
{ std::cout << "non_member_fun( " << a << ", " << b << ", " << c << " )\n" ; return a+b+c ; }


int main()
{
    struct A { void foo( int a ) { std::cout << "main::A::foo( " << this << ", " << a << " )\n" ; } };
    struct B { void bar( int a, char b ) { std::cout << "main::B::bar( " << this << ", " << a << ", " << b << " )\n" ; } };
    const auto closure = [] { std::cout << "main::closure()\n" ; return 9 ; };

    A a ; std::cout << "std::addressof(a): " << std::addressof(a) << '\n' ;
    B b ; std::cout << "std::addressof(b): " << std::addressof(b) << "\n\n" ;

    function_map fmap ;
    fmap.insert( "one", &A::foo, a, 123 ) ; // pass a by value
    fmap.insert( "two", &B::bar, std::ref(b), 456, 'B' ) ; // pass b by wrapped reference
    fmap.insert( "three", closure ) ;
    fmap.insert( "four", non_member_fun, 789, 12.34, 56 ) ;

    for( std::string key : { "two", "four", "three", "one" } )
    {
        std::cout << key << " => " ;
        fmap.call(key) ;
    }

}
