#include <iostream>
#include <string>
#include <vector>
#include <cassert>

class A
{
  public:
    A( int _a ) : a( _a ) {}

    virtual bool operator==( const A& right ) const
    {
        std::cout << "A::==\n";
        return a == right.a;
    }

    virtual bool operator!=( const A& right ) const
    {
        std::cout << "A::!=\n";
        return !( this->operator==(right) );
    }

    int a;
};

class B : public A
{
  public:
    B( int _a, int _b ) : A( _a ), b( _b ) {}

    bool operator==( const A& right ) const override
    {
        std::cout << "B::==\n";
        if (A::operator==( right ))
            if (const B* p = dynamic_cast<const B*>(&right))
                return b == p->b;
        return false;
    }

    int b;
};


int main()
{
    A a4(4), a5(5), a4bis(4);
    assert( a4 == a4bis );
    assert( a4 != a5 );

    B b1(4,5), b2(4,6);
    assert( !(b1 == b2) );
    assert( b1 != b2 ); // fails because B::operator== is not called!
}
