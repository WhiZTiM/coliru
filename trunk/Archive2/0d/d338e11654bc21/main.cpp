#include <iostream>

template < typename X, typename Y > void foo( const X&, const Y& )
{ std::cout << "the general case: foo<X,Y>\n" ; }

// both template type arguments are explicitly specified
template <> void foo<int,int>( const int&, const int& )
{ std::cout << "explicit specialisation: foo<int,int>\n" ; }

// the first template type argument is explicitly specified, the second is deduced from context
template <> void foo<char>( const char&, const char& )
{ std::cout << "explicit specialisation: foo<char,char>\n" ; }

// both template type arguments are deduced from context
template <> void foo( const short&, const short& ) 
{ std::cout << "explicit specialisation: foo<short,short>\n" ; }

// this is not an explicit specilisation. This is an overload of the function foo
// favour overloading function templates (over explicitly specialising function templates)
// see: http://www.gotw.ca/publications/mill17.htm
void foo( const double&, const double& )
{ std::cout << "overload: foo( const double&, const double& )\n" ; }

int main()
{
    foo( 56UL, 71UL ) ; // the general case: foo<X,Y>

    foo( 12, 78 ) ; // explicit specialisation: foo<int,int>
    foo( 'a', 'b' ) ; // explicit specialisation: foo<char,char>
    foo( short(12), short(12) ) ; // explicit specialisation: foo<short,short>

    foo( 2.3, 5.6 ) ; // overload: foo( const double&, const double& )
}
