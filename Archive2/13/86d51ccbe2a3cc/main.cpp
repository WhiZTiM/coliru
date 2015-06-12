
#include <functional>
#include <map>
#include <utility>
#include <typeinfo>
#include <cstddef>
#include <iostream>
#include <iomanip>

using namespace std;


class Base;
class Foo;
class Bar;
class Baz;

typedef pair<size_t,size_t> ti_pair;
typedef function<bool(const Base&,const Base&)> comp_func;

extern void register_all();

class Base
{
public:
    virtual ~Base() = default;
    virtual int my_code() { return typeid(*this).hash_code(); }
    
    static bool compare( const Base& b1,const Base& b2 )
    {
        auto itr = compare_map.find( make_pair( typeid(b1).hash_code(), typeid(b2).hash_code() ) );
        if( itr == compare_map.end() ) throw "error";
        return itr->second(b1,b2);
    }
    
private:
    static map< ti_pair, comp_func > compare_map;
    static void register_comparator(const ti_pair&,const comp_func&);
    
friend
    void register_all();
};

bool operator==( const Base& b1,const Base& b2 ) { return Base::compare(b1,b2); }
    
map< ti_pair, comp_func > Base::compare_map;

void Base::register_comparator(const ti_pair& tip,const comp_func& f)
{
    compare_map[tip]=f;
}

class Foo : public Base
{
public:

};

class Bar : public Base
{
public:

};

class Baz : public Base
{
public:

};

bool compare_foo_bar( const Base& foo_, const Base& bar_ )
{
    const Foo& foo = dynamic_cast<const Foo&>(foo_);
    const Bar& bar = dynamic_cast<const Bar&>(bar_);
    // do actual compare
    return false;
}

bool compare_base_baz( const Base& base, const Base& baz_ )
{
    const Baz& baz = dynamic_cast<const Baz&>(baz_);
    // do actual compare
    return false;
}

void register_all()
{
    auto reg_both = []( size_t ti1, size_t ti2, comp_func f )
    {
        Base::register_comparator( make_pair(ti1,ti2), f );
        Base::register_comparator( make_pair(ti2,ti1), [=](const Base& b1,const Base& b2)->bool { return f(b2,b1); } );
    };
        
    reg_both( typeid(Foo).hash_code(),  typeid(Bar).hash_code(), &compare_foo_bar);
    reg_both( typeid(Base).hash_code(), typeid(Baz).hash_code(), &compare_base_baz);
    
}

int main()
{
    try {
        register_all();
        
        Base base;
        Foo foo;
        Bar bar;
        Baz baz;

        cout << boolalpha << (foo==bar) << endl;
        cout << boolalpha << (baz==base) << endl;
    } catch(...)
    {
        cout << "caught error" << endl;
    }
}

