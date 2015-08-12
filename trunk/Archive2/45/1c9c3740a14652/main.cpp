#include <iostream>
using namespace std;

class Foo {
public:
    template<typename X, typename T, typename U, typename ... Args> static void f( );
    template<typename X, typename T> static void f( );
};


template<typename X, typename T> void Foo::f( ) {
    cout << "Swallowed last two arguments." << endl;
}

template<typename X, typename T, typename U, typename ... Args> void Foo::f( ) {
    cout << sizeof (T ) << endl;
    Foo::f <X, U, Args...>( );
}

int main()
{
    Foo::f<void*, int, double, long>( );
}