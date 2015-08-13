#include <iostream>

struct A
{
    operator short() const { std::cout << "short\n" ; return n ; }
    operator double() const { std::cout << "double\n" ; return n ; }
    std::size_t n = 9 ;
};

struct B
{
    operator short() const { std::cout << "short\n" ; return n ; }
    operator int() const { std::cout << "int\n" ; return n ; }
    operator double() const { std::cout << "double\n" ; return n ; }
    operator const void* () const { std::cout << "const void*\n" ; return this ; }
    std::size_t n = 9 ;
};

void foo(int) {}
void bar(long) {}

int main()
{
    A a ;
    B b ;

    foo(a) ; // short
    // candidate functions: A::operator short() const, A::operator double() const,
    // viable functions: A::operator short() const, A::operator double() const
    // best viable function: A::operator short() const
    // short => int (integral promotion) is better than double => int (other standard conversion)

    foo(b) ; // int
    // candidate functions: operator short(), operator int(), operator double(),  operator const void*() const
    // viable functions: operator short(), operator int(), operator double()
    // best viable function: A::operator int() const
    // int => int (exact match) is better than short =>int (promotion) and double => int (other standard conversion)

    bar(a) ; // *** error: ambiguous
    // candidate functions: A::operator short() const, A::operator double() const
    // viable functions: A::operator short() const, A::operator double() const
    // there is no best viable function.
    // short => long (other standard conversion), double => long (other standard conversion)

    bar(b) ; // *** error: ambiguous
    // ranks of short => long, int => long, double => long are equal (other standard conversion)
}
