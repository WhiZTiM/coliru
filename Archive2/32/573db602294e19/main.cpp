#include <vector>
#include <memory>
#include <iostream>

class A {
public:
    A( int y ) : x(y) {}
    int x;  
};

struct mpq_class
{
    mpq_class() {}
    mpq_class(int, int) {}
    mpq_class(mpq_class const&) {}
    mpq_class& operator=(mpq_class const&) { return *this; }
};

class Obj {
public:
    Obj( mpq_class i, std::vector<std::unique_ptr<A> > v ) : number(i), cont( std::move(v) ) {}

    mpq_class number;
    std::vector<std::unique_ptr<A> > cont;
};

int main()
{
    std::vector<Obj> result;
    mpq_class rational;
    std::vector<std::unique_ptr<A> > abstractObjectsForConstructor;
    result.emplace_back( rational, std::move(abstractObjectsForConstructor) );
}
